#include "Server.hpp"
#include "parsing.hpp"

Server::Server(int port, std::string password) : port_(port), password_(password){}

Server::~Server(){}

void Server::initializeServer(){

    createSocket();
    std::cout << "Server " << server_fd_ << " is connected on port " << port_ << std::endl;
    while(1){

        if(poll(fds_.data(), fds_.size(), -1) == -1)
            throw(std::runtime_error("poll() failed"));
        for(size_t i = 0; i < fds_.size(); i++){
            if(fds_[i].revents && POLLIN){
                if(fds_[i].fd == server_fd_)
                    acceptClient();
                else
                {
                    Client *client = getClient(fds_[i].fd);
                    receiveData(*client);
                }
            }
        }
    }
}

void Server::createSocket(){

    struct sockaddr_in servaddr;
    struct pollfd NewPoll;

    //Creation de la socket

    server_fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd_ == -1)
        throw std::runtime_error("Failed to create socket");

    //Config de l adresse du serveur

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(port_);

    if(fcntl(server_fd_, F_SETFL, O_NONBLOCK) == -1)
        throw(std::runtime_error("problem with fcntl()"));
    if(bind(server_fd_, reinterpret_cast<struct sockaddr*>(&servaddr), sizeof(servaddr)) < 0)
        throw(std::runtime_error("failed to bind socket"));
    if(listen(server_fd_, 5) < 0)
        throw(std::runtime_error("listen failed"));


    // ajoute socket au tableau de fd

    NewPoll.fd = server_fd_;
    NewPoll.events = POLLIN;
    NewPoll.revents = 0;
    fds_.push_back(NewPoll);
}

void Server::acceptClient(){

    Client client;
    struct sockaddr_in cliaddr;
    struct pollfd NewPoll;
    socklen_t len = sizeof(cliaddr);

    int client_fd_ = accept(server_fd_, reinterpret_cast<sockaddr*>(&cliaddr), &len);
    if (client_fd_ == -1)
        throw std::runtime_error("accept() failed");
    if(fcntl(client_fd_, F_SETFL, O_NONBLOCK) == -1)
        throw(std::runtime_error("problem with fcntl()"));

    NewPoll.fd = client_fd_;
    NewPoll.events = POLLIN;
    NewPoll.revents = 0;
    client.setFd(client_fd_);
    clients_.push_back(client);
    fds_.push_back(NewPoll);

    std::cout << "Client " << client_fd_ << " is connected" << std::endl;
}

void Server::receiveData(Client &client){

    char buff[1024];
    memset(buff, 0, sizeof(buff));

    size_t bytes = recv(client.getFd(), buff, sizeof(buff) - 1, MSG_WAITALL);
    if (bytes <= 0) {
        if (bytes == 0) {
            std::cout << "Client " << client.getFd() << " disconnected" << std::endl;
        } else {
            throw std::runtime_error("recv() failed for client ");
        }
        clearClients(client.getFd());
        clearFd(client.getFd());
        close(client.getFd());
    } else {

        buff[bytes] = '\0';
        client.getBuffer().append(buff);
        //print pour buffer
        std::cout << "Client " << client.getFd() << " Data: " << buff << std::endl;
        // std::cout << "Client " << client.getFd() << " Data: " << client.getBuffer()  << std::endl;
        parseBuffer(client);
    }   
}





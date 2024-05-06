#include "Server.hpp"

Server::Server(int port) : port_(port){}

Server::~Server(){}

void Server::initialize(){

    //Creation de la socket
    
    server_fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd_ < 0){

        std::cerr << "Error socket creation " << std::strerror(errno) << std::endl;
        return;
    }

    //Configuration de l adresse du serveur

    address_server_.sin_family = AF_INET;
    address_server_.sin_addr.s_addr = INADDR_ANY;
    address_server_.sin_port = htons(port_);

    //Connection du socket au port

    if(bind(server_fd_, reinterpret_cast<struct sockaddr*>(&address_server_), sizeof(address_server_)) < 0){

        std::cerr << "Error socket binding " << std::strerror(errno) << std::endl;
        return; 
    }

    //Attendre les connexions entrantes

    if(listen(server_fd_, 5) < 0){

        std::cerr << "Error when listening " << std::strerror(errno) << std::endl;
        return; 
    }

    std::cout << "Connection is made on port " << port_ << std::endl;

}

void Server::acceptclient(){

    //Accepter les connections clients

    client_size_ = sizeof(address_client_);
    client_fd_ = accept(server_fd_, reinterpret_cast<struct sockaddr*>(&address_client_), &client_size_);
    if(client_fd_ < 0){
        std::cerr << "Error connexion with client " << std::strerror(errno) << std::endl;
        return;
    }
    
    std::cout << "Accepted new connection on client socket fd : " << client_fd_ << std::endl;
}
#pragma once
#include <iostream>
#include <vector>
#include <poll.h>
#include <cstdlib> // atoi
#include <netinet/in.h> // struct sockaddr_in
#include <stdexcept>
#include <fcntl.h>
#include <unistd.h> // close
#include <cstring> //memset
#include <sstream>
#include "Client.hpp"

class Client;

class Server{

    private :

        int port_;
        std::string password_;
        int server_fd_;
        std::vector <Client> clients_;
        std::vector <struct pollfd> fds_;

        public :

        Server(int port, std::string password);
        ~Server();

        void initializeServer();
        void createSocket();
        void acceptClient();
        void receiveData(Client &Client);
        
        //utils
        void clearClients(int fd);
        Client* getClient(int fd);
        void clearFd(int fd);
        void sendMessage(int sockfd, const std::string& message); 
        int count_params(const std::string& command);

        //parsing
        void parseBuffer(Client &client);

        //pass
        void pass_cmd(std::string &command, Client &client);

        //nick
        void nick_cmd(std::string &command, Client &client);
        
};
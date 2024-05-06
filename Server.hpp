#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <cerrno>

class Server{

    private :

        int port_;
        int server_fd_, client_fd_;
        struct sockaddr_in address_server_;
        struct sockaddr_in address_client_;
        socklen_t client_size_;
    
    public :

        Server(int port);
        ~Server();

        void initialize();
        void acceptclient();
};


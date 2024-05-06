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

class Client{

    private :

        int client_fd;
        struct sockaddr_in address_client_;

    public :

    Client();
    ~Client();
    
    void connecttoserver();
};
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
        static const std::vector<std::string>& get_cmds();
        static std::vector<std::string> create_cmds();


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

        //parsing
       
        void parseBuffer(Client &client);
        int find_cmds(const std::string &command) const;
        void processCommand(const std::string &command, Client &client);
        void pass_command(const std::string &command, Client &client);
        int count_params(const std::string& command);
        void sendMessage(int sockfd, const std::string& message); 
};
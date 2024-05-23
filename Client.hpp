#pragma once
#include "Server.hpp"
#include <map>

class Client{

    private :

        int fd_;

    public :

        Client();
        ~Client();

        int getFd()const;
        void setFd(int fd);
};
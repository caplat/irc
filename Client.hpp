#pragma once
#include "Server.hpp"

class Client{

    private :

        int fd_;
        std::string buffer_;
        std::string nick_;

    public :

        Client(){};
        ~Client(){};

        std::string getBuffer()const { return buffer_; };
        int getFd()const { return fd_; };
        void setFd(int fd) { fd_ = fd; };
        const std::string& getNick()const { return nick_; };
        void setNick(std::string nick) { nick_ = nick; };


};
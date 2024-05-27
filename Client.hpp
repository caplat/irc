#pragma once
#include "Server.hpp"

class Client{

    private :

        int fd_;
        std::string buffer_;
        std::string nick_;
        bool is_registered_;

    public :

        Client() :fd_(-1), buffer_(""), nick_(""), is_registered_(0){};
        ~Client(){};

        std::string& getBuffer() { return buffer_; };
        int getFd()const { return fd_; };
        void setFd(int fd) { fd_ = fd; };
        const std::string& getNick()const { return nick_; };
        void setNick(std::string nick) { nick_ = nick; };
        bool getRegistered(){ return is_registered_; };
        void setRegistered(bool is_registered) {is_registered_ = is_registered; }
};
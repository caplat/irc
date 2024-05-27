#pragma once
#include "Server.hpp"

class Channel{

    private :

        std::vector<Client>clients_;
        std::vector<Client>admin_;
        std::vector<std::pair<char, bool> >modes_;
        std::string password_;
        std::string name_;

    public :

    Channel();
    ~Channel(){};

    void addClient(Client &client);
    void addAdmin(Client &client);
};
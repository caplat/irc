#include "Channel.hpp"

Channel::Channel() : name_(""){

    char characters[5] = {'i', 't', 'k', 'o', 'l'};
    for(int i = 0; i < 5; i++){

         modes_.push_back(std::make_pair(characters[i], false));
    }
};

void Channel::addClient(Client &client){

    clients_.push_back(client);
}

void Channel::addAdmin(Client &client){

    admin_.push_back(client);
}
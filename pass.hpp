#include "Server.hpp"
#include "reply.hpp"

void Server::pass_cmd(std::string &command, Client &client){

    command = command.substr(4);
    size_t pos = command.find_first_not_of("\t\v ");
    if(pos < command.size())
        command = command.substr(pos);
    if(pos == std::string::npos || command.empty())
        sendMessage(client.getFd(), ERR_NEEDMOREPARAMS(client.getNick()));
    else if(client.getRegistered() == 0){

        std::string pass = command;
        if(pass == password_)
            client.setRegistered(true);
        else{
            sendMessage(client.getFd(), ERR_PASSWDMISMATCH(client.getNick()));
            clearClients(client.getFd());
            clearFd(client.getFd());
            close(client.getFd());
        }
    }
    else
        sendMessage(client.getFd(), ERR_ALREADYREGISTERED(client.getNick()));
 }
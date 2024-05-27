#include "Server.hpp"

class Server;

void Server::pass_cmd(std::string &command, Client &client){

    command = command.substr(4);
    size_t pos = command.find_first_not_of("\t\v ");
    if(pos < command.size())
        command = command.substr(pos);
    std::cout << "pass : " << command << std::endl;
    if(pos == std::string::npos || command.empty())
        sendMessage(client.getFd(), ERR_NEEDMOREPARAMS(client.getNick()));
    else if(client.getRegistered() == 0){

        std::string pass = command;
        if(pass == password_)
            client.setRegistered(true);
        else{
            sendMessage(client.getFd(), "ERROR" + ERR_PASSWDMISMATCH(client.getNick()));
            close(client.getFd());
            clearClients(client.getFd());
            clearFd(client.getFd());
        }
    }
    else
        sendMessage(client.getFd(), ERR_ALREADYREGISTERED(client.getNick()));
 }
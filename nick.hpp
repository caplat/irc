#include "Server.hpp"
#include "reply.hpp"

void Server::nick_cmd(std::string &command, Client &client){

    command = command.substr(4);
    size_t pos = command.find_first_not_of("\t\v ");
    if(pos < command.size())
        command = command.substr(pos);
    if(pos == std::string::npos || command.empty())
        sendMessage(client.getFd(), ERR_NONICKNAMEGIVEN(client.getNick()));
}


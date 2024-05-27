#include "Server.hpp"

void Server::nick_cmd(std::string &command, Client &client){

    command = command.substr(4);
    size_t pos = command.find_first_not_of("\t\v ");
    if(pos < command.size())
        command = command.substr(pos);
    std::cout << "nick : " << command << std::endl;
    if(pos == std::string::npos || command.empty()){
        std::cout << "1" << std::endl;
        sendMessage(client.getFd(), ERR_NONICKNAMEGIVEN(client.getNick()));
        return;
    }
    if(is_nick_valid(command) == false){
        std::cout << "2" << std::endl;
        sendMessage(client.getFd(), ERR_ERRONEUSNICKNAME(client.getNick()));
        return;
    }
    if(is_nick_taken(command, client) == true){
        std::cout << "3" << std::endl;
        sendMessage(client.getFd(), ERR_NICKNAMEINUSE(client.getNick()));
        return;
    }
    std::string oldnickname = client.getNick();
    client.setNick(command);
    std::cout << "4" << std::endl;
    sendMessage(client.getFd(), RPL_NICKNAMECHANGE(oldnickname,client.getNick()));
}

bool Server::is_nick_valid(std::string &nick){

    if(nick[0] == '#' || nick[0] == ':' || std::isdigit(nick[0]))
        return false;
    for(size_t i = 0; i < nick.length(); i++){

        if(nick[i] == ' ')
            return false;
        if (!std::isalnum(nick[i]) && nick[i] != '[' && nick[i] != ']' &&
            nick[i] != '{' && nick[i] != '}' && nick[i] != '|' && nick[i] != '\\') {
            return false;
        }
    }
    return true;
}

bool Server::is_nick_taken(std::string &nick, Client &client){

    for(size_t i = 0; i < clients_.size(); i++){

        if(client.getFd() != clients_[i].getFd())
        {
            if(clients_[i].getNick() == nick)
            return true;
        }
    }
    return false;
}
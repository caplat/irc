#include "Server.hpp"
#include "reply.hpp"

void Server::parseBuffer(Client &client){

    std::string buffer = client.getBuffer();
    size_t pos = 0;

    while ((pos = buffer.find("\r\n")) != std::string::npos) {
        std::string command = buffer.substr(0, pos);
        buffer.erase(0, pos + 2);
        if(command.substr(0, 4) == "PASS")
            pass_cmd(command, client);
        else if(command.substr(0, 4) == "NICK")
            nick_cmd(command, client);
    }
}


void Server::nick_cmd(std::string &command, Client &CLient){


}




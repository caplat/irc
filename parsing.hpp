#include "Server.hpp"
#include "reply.hpp"

void Server::parseBuffer(Client &client){

    std::string buffer = client.getBuffer();
    size_t pos = 0;

    while ((pos = buffer.find("\r\n")) != std::string::npos) {
        std::string command = buffer.substr(0, pos);
        buffer.erase(0, pos + 2);
        processCommand(command, client);
    }
}

void Server::processCommand(const std::string &command, Client &client){

    switch(find_cmds(command))
    {
        case 0:
                pass_command(command, client);
    }

}

std::vector<std::string> Server::create_cmds() {
    std::vector<std::string> cmds;
    cmds.push_back("PASS");
    cmds.push_back("NICK");
    cmds.push_back("USER");
    cmds.push_back("JOIN");
    cmds.push_back("PART");
    cmds.push_back("TOPIC");
    cmds.push_back("INVITE");
    cmds.push_back("KICK");
    cmds.push_back("QUIT");
    cmds.push_back("MODE");
    cmds.push_back("PRIVMSG");
    return cmds;
}

const std::vector<std::string>& Server::get_cmds() {
    static const std::vector<std::string> cmds = create_cmds();
    return cmds;
}

int Server::find_cmds(const std::string &command) const {
    const std::vector<std::string>& cmds = get_cmds();

    for (size_t i = 0; i < cmds.size(); ++i) {
        if (command.compare(0, cmds[i].size(), cmds[i]) == 0) {
            return static_cast<int>(i);
        }
    }
    return -1;
}


void Server::pass_command(const std::string &command, Client &client){

    int param = count_params(command);
    if(param != 1){

        sendMessage(client.getFd(), ERR_NEEDMOREPARAMS(client.getNick()));
    }
}

int Server::count_params(const std::string& command) {
    std::istringstream iss(command);
    std::vector<std::string> tokens;
    std::string token;

    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens.size() - 1;
}

void Server::sendMessage(int sockfd, const std::string& message) {

    int bytes_sent = send(sockfd, message.c_str(), message.length(), 0);    
    if (bytes_sent == -1) {
        std::cerr << "Erreur lors de l'envoi du message" << std::endl;
    } else {
        std::cout << "Message envoyé avec succès !" << std::endl;
    }
}
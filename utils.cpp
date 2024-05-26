#include "Server.hpp"

//remove fd from fds_

void Server::clearFd(int fd){

    for(size_t i = 0; i < fds_.size(); i++){

        if(fds_[i].fd == fd){
            fds_.erase(fds_.begin() + i);
            break;
        }
    }

}

//remove client from clients_

 void Server::clearClients(int fd){

    for(size_t i = 0; i < clients_.size(); i++){

            if(clients_[i].getFd() == fd){

            clients_.erase(clients_.begin() + i);
            break;
        }
    }
 }


 Client* Server::getClient(int fd){
	for (size_t i = 0; i < clients_.size(); i++){
		if (clients_[i].getFd() == fd)
			return &clients_[i];
	}
	return NULL;
}

void Server::sendMessage(int sockfd, const std::string& message) {

    int bytes_sent = send(sockfd, message.c_str(), message.length(), 0);    
    if (bytes_sent == -1) {
        std::cerr << "Erreur lors de l'envoi du message" << std::endl;
    } else {
        std::cout << "Message envoyé avec succès !" << std::endl;
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

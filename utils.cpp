#include "Server.hpp"
#include "Client.hpp"

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
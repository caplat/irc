#include "Server.hpp"

int main(int argc, char**argv)
{
    if(argc != 3){

        std::cout << "please retry with ./ircserv <port> <password>";
        return(0);
    }
    Server server(std::atoi(argv[1]));
    server.initialize();
    server.acceptclient();
    return(0);
}




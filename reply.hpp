#ifndef REPLY_HPP
#define REPLY_HPP
#include "Server.hpp"

#define CRLF "\r\n"
#define ERR_NEEDMOREPARAMS(nickname) (": 461 " + nickname + " :Not enough parameters." + CRLF)
#define ERR_ALREADYREGISTERED(nickname) (": 462 " + nickname + " :You may not reregister !" + CRLF )
#define ERR_PASSWDMISMATCH(nickname) (": 464 " + nickname + " :Password incorrect !" + CRLF )

#endif
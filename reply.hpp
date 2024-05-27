#ifndef REPLY_HPP
#define REPLY_HPP

#define CRLF "\r\n"
#define CHANLIMIT 20

#define ERR_NEEDMOREPARAMS(nickname) (": 461 " + nickname + " :Not enough parameters." + CRLF)
#define ERR_ALREADYREGISTERED(nickname) (": 462 " + nickname + " :You may not reregister !" + CRLF )
#define ERR_PASSWDMISMATCH(nickname) (": 464 " + nickname + " :Password incorrect !" + CRLF )

#define ERR_NONICKNAMEGIVEN(nickname) (": 431 " + nickname + " :No nickname given" + CRLF )
#define ERR_ERRONEUSNICKNAME(nickname) (": 432 " + nickname + " :Erroneus nickname" + CRLF)
#define ERR_NICKNAMEINUSE(nickname) (": 433 " + nickname + " :Nickname is already in use" + CRLF)


#define RPL_NICKNAMECHANGE(oldnickname, nickname) (":" + oldnickname + " NICK " + nickname + CRLF)

#endif
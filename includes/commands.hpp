/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu.escande@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:07:04 by matthieu          #+#    #+#             */
/*   Updated: 2022/04/26 16:17:47 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
# define COMMANDS_HPP

#include "irc.hpp"
#include <sstream>


//common errors

class Server;

struct	t_cmd
{
	std::string raw;
	std::string	prefix;
	std::string	command_name;
	std::vector<std::string>	parameters;
	std::string	footer;
	Server*		srv;
};

class	Client;

bool	isChannelName(std::string name);

COMMAND_RET_VAL EXIT(COMMAND_PARAM);
COMMAND_RET_VAL USER(COMMAND_PARAM);
COMMAND_RET_VAL NICK(COMMAND_PARAM);
COMMAND_RET_VAL PASS(COMMAND_PARAM);
COMMAND_RET_VAL JOIN(COMMAND_PARAM);
COMMAND_RET_VAL LIST(COMMAND_PARAM);
COMMAND_RET_VAL PING_PONG(COMMAND_PARAM);
COMMAND_RET_VAL PRIVMSG(COMMAND_PARAM);
COMMAND_RET_VAL PART(COMMAND_PARAM);
COMMAND_RET_VAL TOPIC(COMMAND_PARAM);
COMMAND_RET_VAL MODE(COMMAND_PARAM);
COMMAND_RET_VAL KICK(COMMAND_PARAM);

namespace ERR {
	ERROR_TYPE	NEEDMOREPARAMS(ERR_PARAMETERS);
	ERROR_TYPE	ALREADYREGISTRED(ERR_PARAMETERS);
}
namespace RPL
{
	std::string removeCRLF(const std::string str);
	std::string makeReply(const std::string example, const std::string set, RPL_PARAMETERS);
	REPLY_TYPE	WELCOME(RPL_PARAMETERS);
	REPLY_TYPE	YOURHOST(RPL_PARAMETERS);
	REPLY_TYPE	CREATED(RPL_PARAMETERS);
	REPLY_TYPE	MYINFO(RPL_PARAMETERS);
	REPLY_RET_VAL	byCode(int code, RPL_PARAMETERS);
}
# endif

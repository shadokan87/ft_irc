/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu.escande@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:39:56 by matthieu          #+#    #+#             */
/*   Updated: 2022/04/27 10:17:17 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "irc.hpp"
#include "commands.hpp"

class Channel;
class Server;
struct t_cmd;
struct info
{
	bool registred;
	std::string nick;
	std::string username;
	std::string	realname;
};

class	Client
{
	private:
		std::string		_buffer;
		std::map<std::string, Channel *>	_channels;
		std::map<std::string, Channel *>	_banned;
		info	_info;
		int		_fd;
		bool	_invisible;
		bool	_notifications;
		COMMAND_RET_VAL _execute_one(t_cmd& cmd, Server& srv);
	public:
		Client(int socket);
		~Client();
		std::string read_msg();
		void	addToBuffer(char c);
		void	addToBuffer(char *str);
		str&	getBuffer() { return(_buffer); }
		int		getFd() const { return _fd; }

		void	execute(std::stack<t_cmd> commands, Server& srv);
		void	sendMessage(std::string msg) const;

		bool	inChan(Channel *chan) const;
		bool	inChan(std::string name) const;
		int		joinChan(Channel * chan);
		void	leaveChan(Channel *chan);
		bool	isBannedFrom(Channel * chan) const;
		void	getBanned(Channel * chan);
		void	getUnbanned(Channel *chan);

		std::string		toString() const;
		info&	getInfo();

		bool	isInvisible() const;
		void	setInvisible(bool val);
		bool	isNotified() const;
		void	setNotifications(bool val);
};

bool operator<(class Client lhs, class Client rhs);
bool operator<(class Client lhs, int rhs);

#endif

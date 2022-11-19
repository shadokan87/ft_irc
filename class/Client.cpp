/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu.escande@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 18:03:36 by matthieu          #+#    #+#             */
/*   Updated: 2022/04/27 10:14:51 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

info&	Client::getInfo()
{
	return (_info);
}

Client::Client(int socket) : _buffer(""), _channels(), _banned(), _invisible(false), _notifications(false)
{
	char str_address[INET6_ADDRSTRLEN];
	struct sockaddr_in6 client_socket;
	socklen_t len = sizeof(client_socket);
	bzero(&client_socket, len);

	_info.registred = false;
	_info.nick = "";
	_info.username = "";
	_info.realname = "";

	TEST(_fd = accept(socket, (struct sockaddr*)&client_socket, &len), -1, e_accept());

	$print "(◠﹏◠) New connection " << toString() << " from: "
		<< inet_ntop(client_socket.sin6_family, &client_socket, str_address, INET6_ADDRSTRLEN)
		<< " Using port: " << ntohs(client_socket.sin6_port)
		<< std::endl;
}

Client::~Client() {
	for (std::map<std::string, Channel *>::iterator it = _channels.begin(); it != _channels.end(); ++it) {
		it->second->removeClient(this);
	}
	_channels.clear();
	_banned.clear();
}

void	Client::addToBuffer(char c) {
	_buffer += c;
}
void	Client::addToBuffer(char *str)
{
	int i = 0;
	while (str[i]) {
		_buffer += str[i];
		i++;
	}
}

std::string Client::read_msg() {
	char			_tmpbuff[256];
	ssize_t nbytes = recv(this->_fd, _tmpbuff, sizeof(_tmpbuff), 0);
	if (nbytes == 0) {
		throw e_client_left();
	}
	_buffer += std::string(_tmpbuff, nbytes);
	size_t new_line_pos = _buffer.rfind("\n");
	if (new_line_pos == std::string::npos) {
		return ""; // incomplete message
	}
	std::string tmp_return_buf = std::string(this->_buffer, 0, new_line_pos);
	this->_buffer = std::string(this->_buffer, new_line_pos + 1);
	return (tmp_return_buf);
}

std::string	Client::toString() const {
	//create an output string stream
	std::ostringstream os ;
	os << "Client[" << _fd << "]";
	return os.str();
}

struct commands {
	std::string name;
	COMMAND_RET_VAL (*fn)(COMMAND_PARAM);
};

static const commands cmd_list[] = {
	{"USER", &USER},
	{"PASS", &PASS},
	{"NICK", &NICK},
	{"JOIN", &JOIN},
	{"LIST", &LIST},
	{"EXIT", &EXIT},
	{"PING", &PING_PONG},
	{"PONG", &PING_PONG},
	{"PRIVMSG", &PRIVMSG},
	{"PART", &PART},
	{"TOPIC", &TOPIC},
	{"MODE", &MODE},
	{"KICK", &KICK}
};

COMMAND_RET_VAL Client::_execute_one(t_cmd& cmd, Server& srv)
{
	COMMAND_RET_VAL ret = -1;
	unsigned int i = 0;
	while (i < sizeof(cmd_list)/sizeof(*cmd_list))
	{
		if (i == 3 && !_info.registred)
			return 0;
		if (cmd_list[i].name == cmd.command_name)
			return (cmd_list[i].fn(cmd, this, srv));
		i++;
	}
	return (ret);
}

void	Client::execute(std::stack<t_cmd> commands, Server& srv)
{
	COMMAND_RET_VAL ret;
	while (!commands.empty()) {
		ret = _execute_one(commands.top(), srv);
		(void)ret;
		/* std::cout << commands.top().command_name << std::endl; */
		commands.pop();
	}
}

bool operator<(class Client lhs, class Client rhs) {
	return lhs.getFd() < rhs.getFd();
}
bool operator<(class Client lhs, int rhs) {
	return lhs.getFd() < rhs;
}
void	Client::sendMessage(std::string msg) const {
	/* COLOR(CYAN, msg); */
	std::cout << "=> " << COLOR(CYAN, msg) << std::endl;
	msg += "\r\n";
	send(_fd, msg.c_str(), msg.length(), 0);
}

bool	Client::inChan(std::string name) const {
	return _channels.find(name) != _channels.end();
}
bool	Client::inChan(Channel *chan) const {
	return _channels.find(chan->getName()) != _channels.end();
}
bool	Client::isBannedFrom(Channel * chan) const {
	return _banned.find(chan->getName()) != _banned.end();
}
void	Client::getBanned(Channel * chan) {
	_banned[chan->getName()] = chan;
}
void	Client::getUnbanned(Channel *chan) {
	_banned.erase(chan->getName());
}
int		Client::joinChan(Channel * chan) {
	if (_channels.size() >=CHANNEL_MAX)
		return ERR_TOOMANYCHANNELS;
	_channels[chan->getName()] = chan;
	return 0;
}
void	Client::leaveChan(Channel *chan){
	_channels.erase(chan->getName());
}
bool	Client::isInvisible() const { return _invisible;}
void	Client::setInvisible(bool val) { _invisible = val; }
bool	Client::isNotified() const { return _notifications; }
void	Client::setNotifications(bool val) { _notifications = val; }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu.escande@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 19:51:51 by matthieu          #+#    #+#             */
/*   Updated: 2022/04/17 14:13:31 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <utility>

void	Server::init_server()
{
	(void)_ret;
	const struct sockaddr_in6 sin6 = {
		.sin6_family = AF_INET6,
		.sin6_port = htons(_port),
		.sin6_flowinfo = 0,
		.sin6_addr = in6addr_any,
		.sin6_scope_id = 0,
	};

	int on = 1;

	TEST(_socket = socket(AF_INET6, SOCK_STREAM, 0), -1, e_socket());
	TEST(setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)), -1, e_setsockopt());
	if (bind(_socket, (struct sockaddr*) &sin6, sizeof(sin6)) == -1) {
		$print strerror(errno) << std::endl;
		throw e_bind();
	}
	TEST(listen(_socket, sin6.sin6_port), -1, e_listen());

	FD_SET(_socket, &_select.master);
	FD_SET(STDIN_FILENO, &_select.master);
	_select.fd_max = _socket;
	$print std::setw(65) << "(｡◕‿◕｡)" << std::endl;
}

void Server::run() throw () {
	while (this->_do_select()) {}
}

void Server::_accept_client() throw () {
	Client *new_client = new Client(this->_socket);
	int new_client_fd = new_client->getFd();
	this->_clients[new_client_fd] = new_client;
	FD_SET(new_client_fd, &_select.master);
	if (new_client_fd > this->_select.fd_max) {
		this->_select.fd_max = new_client_fd;
	}
}

template <class InputIterator>
void	printX(std::string name, InputIterator beg, InputIterator end)
{
	std::cout << name << ": " << std::endl;
	if (beg == end)
		std::cout << "<empty>" << std::endl;
	while (beg != end)
	{
		std::cout << *beg << std::endl;
		beg++;
	}
}

static t_cmd	lineToCmdStruct(std::string& msg, Server *srv)
{
	t_cmd	cmd;
	size_t ret;
	cmd.raw = msg;
	msg = RPL::removeCRLF(msg);
	/* exit (0); */
	if (msg[0] == ':') //has a prefix
	{
		cmd.prefix = msg.substr(1, msg.find(" ") - 1);
		msg = msg.substr(msg.find(" ") + 1);
	}
	else
		cmd.prefix = "";
	if (msg.find(":") != (size_t)-1) //has a footer
	{
		cmd.footer = msg.substr(msg.find(":") + 1);
		msg = msg.substr(0, msg.find(":"));
	}
	else
		cmd.footer = "";
	ret = msg.find(" ");
	if (ret != (size_t)-1) //has parameters, command ends at whitespace [CMD] [PARAM]
	{
		cmd.command_name = msg.substr(0, ret);
		msg = msg.substr(ret);
		cmd.parameters = parser::splitBySet(msg, " ");
	}
	else // has no parameters, command is the msg
		cmd.command_name = msg;
	cmd.srv = srv;
#ifdef SHOW_PARSING
	$print "prefix " << BRACKET(cmd.prefix);$print "\n";
	$print "command name " << BRACKET(cmd.command_name);$print "\n";
	printX("parameters", cmd.parameters.begin(), cmd.parameters.end());
	$print "footer " << BRACKET(cmd.footer);$print"\n";
	$print "\n\n\n\n";
#endif
	return (cmd);
}

static std::stack<t_cmd> parseClientResponse(std::string &msg, Server *srv)
{
	std::stack<t_cmd> ret;
	std::vector<std::string> splitEndl = parser::splitBySet(msg, "\n");
	std::vector<std::string>::reverse_iterator rbeg = splitEndl.rbegin();
	std::vector<std::string>::reverse_iterator rend = splitEndl.rend();
	while (rbeg != rend)
	{
		ret.push(lineToCmdStruct(*rbeg, srv));
		rbeg++;
	}
	(void)msg;
	return (ret);
}

int Server::_do_select() throw ( e_select ) {
	fd_set	read_fds = this->_select.master;
	TEST(select(this->_select.fd_max + 1, &read_fds, NULL, NULL, NULL), -1, e_select()); // change to epoll if bugged !!
	if (FD_ISSET(STDIN_FILENO, &read_fds)) { // manage stdin
		// this->_manage_stdin_cmd();
		char c;
		if (read(0, &c, 1) == 0) { // quit with CTRL D
			std::cout << "Asked to nicely quit" << std::endl;
			return 0;
		}
	} else if (FD_ISSET(this->_socket, &read_fds)) {
		this->_accept_client();
	} else {
		for(std::map<int, Client*>::iterator iter = _clients.begin(); iter != _clients.end(); ++iter)
		{
			int fd_client = iter->first;
			Client *client = iter->second;
			if (FD_ISSET(fd_client, &read_fds)) {
				try {
					std::string msg = client->read_msg(); // client read on it's fd to create a buffer
					if (msg.empty()) {
						std::cout << client->toString() << ": no complete msg yet TMP is: [" << client->getBuffer() << "]" << std::endl;
					} else {
						std::cout << "<= " << COLOR(GREEN, msg) << std::endl;
						client->execute(parseClientResponse(msg, this), *this);
					}
				} catch (const e_client_left& e) {
					$print e.what() << client->toString() << std::endl;
					FD_CLR(fd_client, &this->_select.master);
					this->_clients.erase(fd_client);
					delete client;
				}
				break;
			}
		}
	}
	return 1;
}

static int verif_port(const char* port) {
	for (size_t i = 0; i != strlen(port); i++)
		if (!('0' <= port[i] && port[i] <= '9'))
			return -1;
	return atoi(port);
}
bool	Server::testPassowrd(std::string& test)
{
	const int ret = strcmp(test.c_str(), _password);
	return (!ret);
}
Client*	Server::clientExists(const std::string& nick) const
{
		for (std::map<int, Client*>::const_iterator it = _clients.begin(); it != _clients.end(); ++it) {
		if (it->second->getInfo().nick == nick)
			return (it->second);
	}
	return (NULL);
}
bool	Server::channelExists(const std::string& name) const
{
	(void)name;
		for (std::map<std::string, Channel*>::const_iterator it = _channels.begin(); it != _channels.end(); ++it) {
		if (it->second->getName() == name)
			return (true);
	}
	return (false);
}
Server::Server(char** argv) : _password(argv[2]), _clients(), _channels() {
	int p = verif_port(argv[1]);
	if (p >= 0) {
		_port = p;
	}
	else
		throw e_server_init();
}
Server::~Server() {
	for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
		delete it->second;
	}
	_clients.clear();
	for (std::map<std::string, Channel *>::iterator it = _channels.begin(); it != _channels.end(); ++it) {
		delete it->second;
	}
	_channels.clear();
}
std::map<std::string, Channel*>	Server::getChannels() const {
	return _channels;
}
std::map<int, Client*>			Server::getClients() const {
	return _clients;
}

void	Server::add_channel(Client* client, std::string name, std::string key) {
	_channels[name] = new Channel(client, name, key);
}
void	Server::removeChannel(std::string name) {
	Channel *tmp = _channels[name];
	_channels.erase(name);
	delete tmp;
}

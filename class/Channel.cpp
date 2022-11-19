/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu.escande@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 22:19:23 by matthieu          #+#    #+#             */
/*   Updated: 2022/04/26 15:33:40 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(Client *c, std::string name, std::string password) : _clients() , _operators(),
	_name(name), _password(password),
	_max_clients(CLIENT_MAX),
	_secret(false),
	_password_protected(false),
	_subject_op(false)
{
	_clients[c->getFd()] = c;
	_operators[c->getFd()] = c;
	if (!password.empty())
		_password_protected = true;
}
Channel::~Channel() {}

std::string		Channel::getName() const { return _name; }
void			Channel::setName(std::string name) { _name = name; }
std::string		Channel::getSubject() const { return _subject; }
void			Channel::setSubject(std::string name) { _subject = name; }
std::string		Channel::getPassword() const { return _password; }
void			Channel::setPassword(std::string name) { _password = name; }

int		Channel::addClient(Client *c) {
	if (_clients.size() >= _max_clients)
		return ERR_CHANNELISFULL;
	_clients[c->getFd()] = c;
	return 0;
}
void	Channel::removeClient(Client *c) {
	_clients.erase(c->getFd());
}

void	Channel::addOperator(Client *c) {
	_operators[c->getFd()] = c;
}
void	Channel::removeOperator(Client *c) {
	_operators.erase(c->getFd());
}

void	Channel::sendMessage(std::string msg) const {
	for (std::map<int, Client *>::const_iterator it = _clients.begin(); it != _clients.end(); ++it) {
		it->second->sendMessage(msg);
	}
}

bool	Channel::isOperator(Client *c) const {
	return (_operators.find(c->getFd()) != _operators.end());
}

Client*	Channel::getClient(Client *c) const {
	std::pair<const int, Client*> tmp = *_clients.find(c->getFd());
	if (tmp == *(_clients.end()))
		return NULL;
	return tmp.second;
}
Client*	Channel::getClient(std::string name) const {
	for (std::map<int, Client *>::const_iterator it = _clients.begin(); it != _clients.end(); ++it) {
		if (it->second->getInfo().nick == name)
			return it->second;
	}
	return NULL;
}
void	Channel::setMaxClient(size_t val) { _max_clients = val; }
size_t	Channel::getMaxClient() const { return _max_clients; }

void	Channel::addBanMask(std::string mask) { _banMask.push_back(mask); }
void	Channel::removeBanMask(std::string mask) {
	for (std::vector<std::string>::iterator it = _banMask.begin(); it != _banMask.end(); ++it) {
		if (*it == mask) {
			_banMask.erase(it);
			return ;
		}
	}
}
std::vector<std::string>&	Channel::getBanMask() { return _banMask; }

std::map<int, Client*>		Channel::getClientCpy() const
{
	std::map<int, Client*> ret(_clients.begin(), _clients.end());
	return (ret);
}
std::map<int, Client*>&		Channel::getClients() { return _clients; }

bool	Channel::isSecret() const { return _secret; }
bool	Channel::isPasswordProtected() const { return _password_protected; }
bool	Channel::isSubjectOp() const { return _subject_op; }

void	Channel::setSecret(bool v) {_secret = v; }
void	Channel::setPasswordProtected(bool v) { _password_protected = v; }
void	Channel::setSubjectOp(bool v) { _subject_op = v; }

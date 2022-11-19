/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu.escande@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 22:09:23 by matthieu          #+#    #+#             */
/*   Updated: 2022/04/26 11:47:09 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "irc.hpp"
#include "Client.hpp"

class Channel {
	private:
		std::map<int, Client *> _clients;
		std::map<int, Client *> _operators;
		std::string		_name;
		std::string		_subject;
		std::string		_password;
		std::vector<std::string>	_banMask;
		size_t	_max_clients;

		bool	_secret;
		bool	_password_protected;
		bool	_subject_op;

	public:
		Channel(Client *, std::string name, std::string password = "");
		virtual ~Channel();

		std::string		getName() const;
		void			setName(std::string name);
		std::string		getSubject() const;
		void			setSubject(std::string name);
		std::string		getPassword() const;
		void			setPassword(std::string name);

		int		addClient(Client *c);
		void	removeClient(Client *c);
		void	addOperator(Client *c);
		void	removeOperator(Client *c);
		void	sendMessage(std::string msg) const;
		bool	isOperator(Client *c) const;
		Client*	getClient(Client *) const;
		Client*	getClient(std::string name) const;
		void	setMaxClient(size_t val);
		size_t	getMaxClient() const;
		void	addBanMask(std::string);
		void	removeBanMask(std::string);
		std::vector<std::string>&	getBanMask();
		std::map<int, Client*>		getClientCpy() const;
		std::map<int, Client*>&		getClients();

		bool	isSecret() const;
		bool	isPasswordProtected() const;
		bool	isSubjectOp() const;

		void	setSecret(bool v);
		void	setPasswordProtected(bool v);
		void	setSubjectOp(bool v);
};

#endif

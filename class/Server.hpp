/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu.escande@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 23:22:40 by matthieu          #+#    #+#             */
/*   Updated: 2022/04/17 14:09:28 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "irc.hpp"
#include "Channel.hpp"

class Client;
class Channel;

class	Server {
	private:
		struct select_data
		{
			fd_set	master;
			int		fd_max;
		};

		const char* _password;
		int		_port;
		int		_socket;
		int		_ret;
		struct select_data	_select;

		std::map<int, Client*> _clients;
		std::map<std::string, Channel*> _channels;

		int		_do_select() throw( e_select );
		void	_accept_client() throw();

	public:
		Server(char** argv = NULL);
		bool	testPassowrd(std::string& test);
		Client*	clientExists(const std::string& nick) const;
		bool	channelExists(const std::string& name) const;
		virtual ~Server();
		void	init_server();
		void	run() throw();
		int		getsocket() const { return _socket; }
		int		getport() const { return _port; }
		void	remove_client(); //TODO ?
		void	add_channel(Client* client, std::string name, std::string key);
		void	removeChannel(std::string name);
		std::map<std::string, Channel*> getChannels() const;
		std::map<int, Client*> getClients() const;
};

#endif

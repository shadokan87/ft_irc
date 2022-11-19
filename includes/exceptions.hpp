/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exceptions.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu.escande@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 23:23:54 by matthieu          #+#    #+#             */
/*   Updated: 2022/04/01 18:27:14 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include "irc.hpp"

#define __exception__ class
#define $set_what(WHAT) 	virtual const char* what() const throw()	{ return (WHAT); }

#define CREATE_EXCEPTION(NAME, MSG) \
class NAME: public irc_exception { public: NAME() : irc_exception(MSG) {} };

class	irc_exception : public std::exception {
	private:
		const std::string msg;
	public:
		irc_exception(const std::string &m) : msg(m) {
		}
		virtual ~irc_exception() throw() {}
		virtual const char* what() const throw()	{ return msg.c_str(); }
};

CREATE_EXCEPTION(e_server_init, "Server initialization failed.")
CREATE_EXCEPTION(e_listen, "listen() failed.")
CREATE_EXCEPTION(e_bind , "bind() failed.")
CREATE_EXCEPTION(e_setsockopt , "setsockopt() failed.")
CREATE_EXCEPTION(e_socket , "socket() failed.")
CREATE_EXCEPTION(e_select , "select() failed.")
CREATE_EXCEPTION(e_accept, "accept() failed.")

CREATE_EXCEPTION(e_client_left, "Client has left")

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu.escande@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:56:35 by matthieu          #+#    #+#             */
/*   Updated: 2022/04/26 17:34:42 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
#define IRC_HPP

#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <map>
#include <vector>
#include <stack>
#include <utility>
#include <arpa/inet.h>
#include <iomanip>
#include <cerrno>
#include <string>
#include <exception>
#include <list>
#include <set>
#include <unistd.h>
#include <cstring>

#define SERVER_NAME "shadokan"

#define BRACKET(X) "[" << X << "]"
# define DG(f,...) dprintf(1, "\033[31m%s\033[0m-\033[35m%d\033[0m: \033[33m" f "\033[0m\n", __func__, __LINE__, ##__VA_ARGS__)
#define $print std::cout <<
#define TEST(RET, ERR, EXCEPT) if ((RET) == ERR) throw EXCEPT;
#define CLIENT_MAX 1000
#define CHANNEL_MAX 1000
/* #define SHOW_PARSING */
/* #define SHOW_FUNC */
#define SHOW_MAKEREPLY
#define COMMAND_PARAM t_cmd &params, Client* client, Server& srv
#define COMMAND_RET_VAL int
#define REPLY_RET_VAL std::string
#define ERROR_TYPE REPLY_RET_VAL
#define REPLY_TYPE REPLY_RET_VAL
#define RPL_PARAMETERS std::map<std::string, std::string> p
#define ERR_PARAMETERS std::map<std::string, std::string> p

#define subExpr(lhs, rhs) exprs.insert(std::make_pair(lhs, rhs));
#define prepare_message(errcode, block) { \
	\ std::map<std::string, std::string> exprs; \
	block}
#define clearExpr exprs.clear()


#define CYAN    "\033[36m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define RESET   "\033[0m"
#define COLOR(C, M) C << M << RESET

typedef std::string str;

#include "exceptions.hpp"
#include "error_define.hpp"
#include "command_answer_define.hpp"
#include "commands.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"

#define PREFIX 0
#define CMD 1

namespace parser{
	size_t countOccurence(std::string& line, const std::string& set);
	bool	isInSet(char c, const std::string& set);
	std::vector<std::string> splitBySet(std::string& line, const std::string& set);
	template <class InputIterator>
		void	printX(std::string name, InputIterator beg, InputIterator end);
}

#endif

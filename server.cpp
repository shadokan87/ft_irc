#include <algorithm>
#include <cstdlib>
#include <exception>
#include <pthread.h>
#include <stdlib.h>
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <map>
#include <utility>
#include <arpa/inet.h>
#include <string>
#include <curses.h>
#include <iomanip>

#define $print std::cout <<
#define $listen_socket __LISTEN_SOCK__(
#define __exception__ class
#define $set_what(WHAT) 	virtual const char* what() const throw()	{ return (WHAT); }
#define SERVER_IS_RUNNING while (1)
#define TEST(RET, ERR, EXCEPT) if ((RET) == ERR) throw EXCEPT;
#define TEST_FAILED (server.ret < 0)

typedef std::string str;
struct select
{
	fd_set master;
	fd_set read_fds;
	int	fd_max;
	int	newConnection;
};
struct var
{
	struct select select;
	struct sockaddr_in client_socket;
};
struct global
{
	struct sockaddr_in server_socket;
	struct var var;
	int port;
	int	socket;
	int	ret;
	char clear[4];
};

global server;

__exception__	server_init : public std::exception { public: server_init() {} $set_what("Server initialization failed."); };
__exception__	_listen : public std::exception { public: _listen() {} $set_what("listen() failed."); };
__exception__	_bind : public std::exception { public: _bind() {} $set_what("bind() failed."); };
__exception__	_setsockopt : public std::exception { public: _setsockopt() {} $set_what("setsockopt() failed."); };
__exception__	_socket : public std::exception { public: _socket() {} $set_what("socket() failed."); };
__exception__	_select : public std::exception { public: _select() {} $set_what("select() failed."); };
__exception__	_accept : public std::exception { public: _accept() {} $set_what("accept() failed."); };

void	init_server()
{
	server.clear[0] = '\033';
	server.clear[1] = 'c';
	server.clear[2] = '\0';
	server.server_socket.sin_family = AF_INET;
	server.server_socket.sin_port = htons(server.port);
	server.server_socket.sin_addr.s_addr = htonl(INADDR_ANY);

	TEST(server.socket = socket(AF_INET, SOCK_STREAM, 0), -1, _socket());
	TEST(bind(server.socket,(struct sockaddr*)&server.server_socket,sizeof(server.server_socket)),-1, _bind());
	TEST(listen(server.socket, server.server_socket.sin_port), -1, _listen());

	FD_SET(server.socket, &server.var.select.master);
	server.var.select.fd_max = server.socket;
	write(0, server.clear, 2);
	$print std::setw(65) << "(｡◕‿◕｡)" << std::endl;
}
int	safe_exit()
{
	return (1);
}
void	server_routine()
{
}

void	new_connection()
{
	char ipv4[INET_ADDRSTRLEN];
	socklen_t len = sizeof(server.var.client_socket);
	TEST(server.var.select.newConnection = accept(server.socket, (struct sockaddr*)&server.var.client_socket, &len), -1, _accept());
	FD_SET(server.var.select.newConnection, &server.var.select.master);
	if (server.var.select.newConnection > server.var.select.fd_max)
		server.var.select.fd_max = server.var.select.newConnection;
	$print "(◠﹏◠) New connection from: "
		<< inet_ntop(server.var.client_socket.sin_family, &server.var.client_socket, ipv4, INET_ADDRSTRLEN)
		<< " Using port: " << server.var.client_socket.sin_port
		<< std::endl;
}
void	do_select()
{
	socklen_t len;
	server.var.select.read_fds = server.var.select.master;
	TEST(select(server.var.select.fd_max + 1, &server.var.select.read_fds, NULL, NULL, NULL), -1, _select());
	for (int i = 0;i < server.var.select.fd_max + 1;i++)
	{
		if (FD_ISSET(i, &server.var.select.read_fds) && i == server.socket)
			new_connection();
	}
}
int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		$print "You forgot the port. (҂◡_◡)" << std::endl;
		exit (1);
	}
	try{ server.port = atoi(argv[1]); init_server(); }
	catch (const std::exception& e) { $print e.what(); safe_exit(); }
	SERVER_IS_RUNNING {
		do_select();
	}
	$print "Bye !";
	safe_exit();
	return (0);
}

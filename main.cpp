#include <algorithm>
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

#define SERVER_IS_RUNNING while (1)
#define $SERVER_PORT 9002
#define $SERVER_ADDR INADDR_ANY
#define $SERVER_SOCKET_PARAMS AF_INET, SOCK_STREAM, 0
#define $SERVER_SOCKET_FN socket
#define $SERVER_SOCKET_ERRNO -1
#define print std::cout << 
#define $EXIT_NOW(MESSAGE, ERRN) print MESSAGE << std::endl << "exiting now." << std::endl;exit(ERRN);
#define MAX_CLIENT 10000
#define $$new_connection_received if (FD_ISSET(server_socket, &collection.read_fds))
#define FD_ZERO_COLLECTION	FD_ZERO(&collection.read_fds); \
							FD_ZERO(&collection.write_fds); \
							FD_ZERO(&collection.except_fds);
typedef std::string str;
struct event
{
	fd_set read_fds,
		   write_fds,
		   except_fds;
	int max_fd;
	int	eventType;
};
int	WAIT_FOR_EVENT(event collection)
{
	return (select(collection.max_fd + 1,
				&collection.read_fds,
				&collection.write_fds,
				&collection.except_fds, NULL));
}
struct	someone
{
	str nick;
	struct sockaddr_in addr;
};
std::map<int, someone> peers;
void	log_new_connection(struct someone& newpeer)
{
	char ipv4[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &newpeer.addr.sin_addr, ipv4, INET_ADDRSTRLEN);
	print "New connection from: " << ipv4 << " " << newpeer.addr.sin_port << std::endl;
}
int	PUSH_NEW_PEER(int server_socket)
{
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	socklen_t len = sizeof(addr);
	int peer_sock = accept(server_socket,
			(struct sockaddr*) &addr, &len);
	if (peer_sock == -1)
		return (-1);
	someone newpeer;
	newpeer.nick = "";
	newpeer.addr = addr;
	peers.insert(std::make_pair(peer_sock, newpeer));
	log_new_connection(newpeer);
	return (peer_sock);
}
int	getFD_ISSET(struct event& collection)
{
	if (peers.empty())
		return (-1);
	std::map<int, someone>::iterator s = peers.begin();
	std::map<int, someone>::iterator e = peers.end();
	int socket = s->first;
	while (s != e)
	{
		if (FD_ISSET(socket, &collection.write_fds))
		{
			collection.eventType = 1;
			return (socket);
		}
		if (FD_ISSET(socket, &collection.read_fds))
		{
			collection.eventType = 2;
			return (socket);
		}
		if (FD_ISSET(socket, &collection.except_fds))
		{
			collection.eventType = 3;
			return (socket);
		}
		s++;
		socket = s->first;
	}
	return (-1);
}
void	exec_write(struct event& collection, int socket)
{
	print "write";
}
void	exec_read(struct event& collection, int socket)
{
	print "read";
}
void	exec_except(struct event& collection, int socket)
{
	print "except";
}
void	exec_eventType(struct event& collection, int socket)
{
	if (socket == -1)
		return ;
	switch (socket)
	{
		case 1:
			exec_write(collection, socket);
		case 2:
			exec_read(collection, socket);
		case 3:
			exec_except(collection, socket);
	}
}
int	main(int argc, char **argv)
{
	print "Irc server started" << std::endl;
	if (argc != 2)
	{
		$EXIT_NOW("You forgot the port.", 1);
	}
	int server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (server_socket == -1)
		{ $EXIT_NOW("server socket", 1); }
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(argv[1]));
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	if ((bind(server_socket, (struct sockaddr*)&server, sizeof(server))) == -1)
		{ $EXIT_NOW("bind failed", 2); }
	int reuse = 1;
	if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) != 0)
		{ $EXIT_NOW("reuse failed", 3); }
	if (listen(server_socket, server.sin_port) == -1)
		{ $EXIT_NOW("listen failed", 4); }
	print "Port: " << argv[1] << std::endl;
	print "Address: " << server.sin_addr.s_addr << std::endl;
	//nonblock
	int flag = fcntl(STDIN_FILENO, F_GETFL, 0);
  	flag |= O_NONBLOCK;
  	fcntl(STDIN_FILENO, F_SETFL, flag);

	event collection;

	//init
	collection.max_fd = server_socket + 1;
	FD_ZERO_COLLECTION;
	FD_SET(server_socket, &collection.read_fds);
	SERVER_IS_RUNNING
	{
		int ret;
		int __event = WAIT_FOR_EVENT(collection);
		switch (__event)
		{
			case -1:
				$EXIT_NOW("select error", 1);
			case 0:
				$EXIT_NOW("select unexpected behavior", 1);
			default:
				$$new_connection_received
					ret = PUSH_NEW_PEER(server_socket);
				if (ret == -1)
					$EXIT_NOW("PUSH_NEW_PEER error", 1);
				if (ret > collection.max_fd)
					collection.max_fd = ret;
				exec_eventType(collection, getFD_ISSET(collection));
				FD_SET(ret, &collection.read_fds); // add new peer's socket to read_fds
		}
	}
	print "bye" << std::endl;
	return (0);
}

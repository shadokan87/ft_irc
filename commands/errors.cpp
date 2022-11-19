#include "commands.hpp"
#include <sstream>

struct	lookup
{
	int code;
	REPLY_RET_VAL	(*fn)(RPL_PARAMETERS);
};

namespace ERR
{
std::string getErrorPrefix(int errcode, Client* client)
{
	(void)client;
	(void)errcode;
	std::stringstream ss;
	std::string _errcode;
	ss << errcode;
	ss >> _errcode;
	std::map<std::string, std::string> p;
	p.insert(std::make_pair("errno", SERVER_NAME));
	p.insert(std::make_pair("server", SERVER_NAME));
	p.insert(std::make_pair("username", client->getInfo().username));
	p.insert(std::make_pair("nick", client->getInfo().nick));
	return (RPL::makeReply(ERR_PREFIX, "<>", p));
}
ERROR_TYPE NEEDMOREPARAMS(ERR_PARAMETERS)
{
	return (RPL::makeReply("<server> 461 <command> :Not enough parameters", "<>", p));
}

ERROR_TYPE ALREADYREGISTRED(ERR_PARAMETERS)
{
	(void)p;
	return (":You may not reregister");
}
}

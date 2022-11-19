#include "commands.hpp"
struct	lookup
{
	int code;
	REPLY_RET_VAL	(*fn)(RPL_PARAMETERS);
};

template <class InputIterator>
void	printX(std::string name, InputIterator beg, InputIterator end)
{
	std::cout << name << ": " << std::endl;
	if (beg == end)
		std::cout << "<empty>" << std::endl;
	while (beg != end)
	{
		std::cout << "[" << *beg <<"]"<< std::endl;
		beg++;
	}
}

namespace RPL{
std::string removeCRLF(const std::string str)
{
	std::string::const_iterator beg = str.begin();
	std::string::const_iterator end = str.end();
	std::string ret = "";
	while (beg != end)
	{
		if (*beg != '\r' && *beg != '\n')
			ret += *beg;
		beg++;
	}
	return (ret);
}
std::string makeReply(const std::string example, const std::string set, RPL_PARAMETERS)
{
	std::string ret = "";
	std::string example_copy = example;
	if (set.find("[") == (size_t)-1 && example_copy.find("["))
		example_copy = example_copy.substr(0, example_copy.find("["));
	std::vector<std::string> split = parser::splitBySet(example_copy, set);
	std::vector<std::string>::iterator beg = split.begin();
	std::vector<std::string>::iterator end = split.end();
	std::map<std::string, std::string>::iterator mp_end = p.end();
	std::map<std::string, std::string>::iterator mp_find_ret;
	(void)mp_end;
	while (beg != end)
	{
		mp_find_ret = p.find(*beg);
		if (mp_find_ret == mp_end)
			ret += *beg;
		else
			ret += mp_find_ret->second;
		beg++;
	}
	return (ret);
}
/* https://dd.ircdocs.horse/refs/numerics/001.html */
REPLY_TYPE	WELCOME(RPL_PARAMETERS) //nick, user, host
{
	return (makeReply(":<server> 001 <nick> :Welcome to the <network> Network, <nick>[!<user>@<host>]", "<>", p));
}
/* https://dd.ircdocs.horse/refs/numerics/002.html */
REPLY_TYPE	YOURHOST(RPL_PARAMETERS) //servername, runningVersion
{
	return (makeReply(":<server> 002 <nick> :Your host is <servername>, running version <version>", "<>", p));
}

REPLY_TYPE	CREATED(RPL_PARAMETERS)
{
	return (makeReply(":<server> 003 <nick> :This server was created <datetime>", "<>", p));
}

REPLY_TYPE	MYINFO(RPL_PARAMETERS)
{
	std::cout << "here" << std::endl;
	return (makeReply(":<server> 004 <nick> <servername> <version> <available umodes> <available cmodes> [<cmodes with param>]", "<>", p));
}

static const lookup lookup_rpl[4] =
{
	{1, WELCOME},
	{2, YOURHOST},
	{3, CREATED},
	{4, MYINFO}
};

REPLY_RET_VAL	byCode(int code, RPL_PARAMETERS)
{
	return (lookup_rpl[code].fn(p));
}
}

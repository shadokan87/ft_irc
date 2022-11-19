#include "irc.hpp"
#define PING_SYNTAX "PING : <nick>"
#define PONG_SYNTAX "PONG : <nick>"
COMMAND_RET_VAL PING_PONG(COMMAND_PARAM)
{
	(void)params;
	(void)client;
	(void)srv;
	std::map<std::string, std::string> p;
	COMMAND_RET_VAL ret = 0;
	#ifdef SHOW_FUNC
	std::cout << COLOR(YELLOW, __PRETTY_FUNCTION__) << std::endl;
	#endif
	if (params.command_name == "PING")
		client->sendMessage("PONG");
	return (ret);
}

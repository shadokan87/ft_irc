#include "irc.hpp"
#define TEST_REPLY ":<nick>!<username>@<ip> PRIVMSG <receiver> :<msg>"
#define S_ERR_401 ":<ip> 401 <nick> :<receiver> :No such nick/channel"
static void error(COMMAND_PARAM)
{
	(void)params;
	(void)client;
	(void)srv;
	std::map<std::string, std::string> p;
	p["ip"] = "0.0.0.0";
	p["nick"] = client->getInfo().nick;
	p["receiver"] = params.parameters[0];
	std::string msg = RPL::makeReply(S_ERR_401, "<>", p);
	client->sendMessage(msg);
}
static void	PRIVMSG_CHANNEL(COMMAND_PARAM)
{
	(void)params;
	(void)client;
	(void)srv;
	#ifdef SHOW_FUNC
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
	if (!srv.channelExists(params.parameters[0]))
	{
			error(params, client, srv);
			return;
	}
	std::map<std::string, std::string> p;
	p["nick"] = client->getInfo().nick;
	p["username"] = client->getInfo().username;
	p["ip"] = "0.0.0.0";
	p["receiver"] = params.parameters[0];
	p["msg"] = params.footer;
	p["server"] = SERVER_NAME;
	std::string msg = RPL::makeReply(TEST_REPLY, "<>", p);
	std::cout << BRACKET(msg) << std::endl;
	std::map<std::string, Channel*> _channels = srv.getChannels();
	std::map<int, Client*> clients = _channels[params.parameters[0]]->getClients();
	for (std::map<int, Client*>::iterator beg = clients.begin(); beg != clients.end(); ++beg)
	{
		if ((*beg).second->getInfo().nick != client->getInfo().nick)
			(*beg).second->sendMessage(msg);
	}
}

COMMAND_RET_VAL PRIVMSG(COMMAND_PARAM)
{
	(void)params;
	(void)client;
	(void)srv;
	std::map<std::string, std::string> p;
	COMMAND_RET_VAL ret = 0;
	#ifdef SHOW_FUNC
	std::cout << COLOR(YELLOW, __PRETTY_FUNCTION__) << std::endl;
	#endif
	if (params.parameters[0][0] == '#')
		PRIVMSG_CHANNEL(params, client, srv);
	else
	{
		DG();
		Client* receiver = srv.clientExists(params.parameters[0]);
		if (!receiver)
		{
			DG();
			error(params, client, srv);
			return (ret);
		}
		p["nick"] = client->getInfo().nick;
		p["username"] = client->getInfo().username;
		p["ip"] = "0.0.0.0";
		p["receiver"] = params.parameters[0];
		p["msg"] = params.footer;
		std::string msg = RPL::makeReply(TEST_REPLY, "<>", p);
		receiver->sendMessage(msg);
	}
	return (ret);
}

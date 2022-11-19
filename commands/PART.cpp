/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PART.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu.escande@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 15:01:46 by matthieu          #+#    #+#             */
/*   Updated: 2022/04/27 11:57:00 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "irc.hpp"

/*
 * http://abcdrfc.free.fr/rfc-vf/rfc1459.html#421
 */
/* Commande: PART */
/* Paramètres: <canal>{,< canal >} */

/* Le message PART provoque le retrait du client expéditeur de la liste des utilisateurs actifs pour tous les canaux listés dans la chaîne de paramètres. */

/* Réponses numériques: */

/*            ERR_NEEDMOREPARAMS              ERR_NOSUCHCHANNEL */
/*            ERR_NOTONCHANNEL */

/* Exemples: */

/* PART #twilight_zone ; quitte le canal "#twilight_zone" */
/* PART #oz-ops,&group5 ; quitte les canaux "&group5" et "#oz-ops". */

static void	reply(Client* client, std::string name, std::map<std::string, Channel*> channel)
{
	(void)name;
	(void)channel;
	std::map<int, Client*> clients = channel[name]->getClients();
	std::cout << COLOR(YELLOW, "here") << std::endl;
	std::map<std::string, std::string> p;
	p["channel"] = name;
	p["nick"] = client->getInfo().nick;
	p["username"] =  client->getInfo().username;
	p["hostname"] = "";
	p["commande"] = "PART";
	p["server"] = SERVER_NAME;
	for (std::map<int, Client*>::iterator beg = clients.begin(); beg != clients.end(); ++beg)
	{
		p["nick2"] = beg->second->getInfo().nick;
		beg->second->sendMessage(RPL::makeReply(S_RPL_KEEPINTOUCH, "<>", p));
	}
	//-c -p -w
	client->sendMessage(RPL::makeReply(S_RPL_KEEPINTOUCH, "<>", p));
}

COMMAND_RET_VAL PART(COMMAND_PARAM) {
	std::vector<std::string> p = params.parameters;
	std::map<std::string, Channel*> _channels = srv.getChannels();
	COMMAND_RET_VAL ret = 0;
	std::map<std::string, std::string> errMap;
	{
		errMap["commande"] = params.command_name;
		errMap["UserID"] = client->getInfo().nick;
		errMap["server"] = SERVER_NAME;
	}
	if (p.size() == 0) {
		client->sendMessage(RPL::makeReply(S_ERR_NEEDMOREPARAMS, "<>", errMap));
		return ERR_NEEDMOREPARAMS;
	}
	do {
		size_t chan_pos = p[0].find_first_of(',');
		std::string name = p[0].substr(0, chan_pos);
		if (chan_pos >= p[0].length()) {
			p[0].clear();
		} else {
			p[0] = p[0].substr(chan_pos);
		}
		if (_channels.find(name) != _channels.end()) {
			if (!client->inChan(name)) {
				errMap["canal"] = name;
				client->sendMessage(RPL::makeReply(S_ERR_NOTONCHANNEL, "<>", errMap));
				return ERR_NOTONCHANNEL;
			}
			_channels[name]->removeClient(client);
		} else {
			client->sendMessage(RPL::makeReply(S_ERR_NOSUCHCHANNEL, "<>", errMap));
			return ERR_NOSUCHCHANNEL;
		}
		reply(client, name, _channels);
	} while(!p[0].empty());
	#ifdef SHOW_FUNC
	DG();
	#endif
	return (ret);
}

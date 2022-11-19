/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPIC.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu.escande@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 15:01:46 by matthieu          #+#    #+#             */
/*   Updated: 2022/04/27 10:57:33 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "irc.hpp"

/*
 * http://abcdrfc.free.fr/rfc-vf/rfc1459.html#424
 */
/* Commande: TOPIC */
/* Paramètres: <canal> [<sujet>] */

/* Le message TOPIC est utilisé pour modifier ou voir le sujet d'un canal. Le sujet du canal <canal> est renvoyé s'il n'y a pas de <sujet> fourni en paramètre. Si le paramètre <sujet> est présent, le sujet du canal changera si le mode du canal le permet. */

/* Réponses numériques : */

/*            ERR_NEEDMOREPARAMS              ERR_NOTONCHANNEL */
/*            RPL_NOTOPIC                     RPL_TOPIC */
/*            ERR_CHANOPRIVSNEEDED */

/* Exemples: */

/* :Wiz TOPIC #test :New topic ; L'utilisateur Wiz définit le sujet. */
/* TOPIC #test :another topic ; Change le sujet du canal #test en "another topic". */
/* TOPIC #test ; Vérifie le sujet de #test. */

COMMAND_RET_VAL TOPIC(COMMAND_PARAM) {
	std::vector<std::string> p = params.parameters;
	std::map<std::string, Channel*> _channels = srv.getChannels();
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
	std::string name = p[0];
	errMap["canal"] = name;
	if (_channels.find(name) == _channels.end()) {
		client->sendMessage(RPL::makeReply(S_ERR_NOTONCHANNEL, "<>", errMap));
		return ERR_NOTONCHANNEL;
	}
	Channel* chan = srv.getChannels()[name];
	if (params.footer.empty() && *(params.raw.rbegin()) != ':') {
		if (chan->getSubject().empty()) {
			client->sendMessage(RPL::makeReply(S_RPL_NOTOPIC, "<>", errMap));
			return RPL_NOTOPIC;
		}
		errMap["sujet"] = _channels[name]->getSubject();
		client->sendMessage(RPL::makeReply(S_RPL_TOPIC, "<>", errMap));
		return RPL_TOPIC;
	}
	if (!client->inChan(name)) {
		client->sendMessage(RPL::makeReply(S_ERR_NOTONCHANNEL, "<>", errMap));
		return ERR_NOTONCHANNEL;
	}
	if (chan->isSubjectOp() && !chan->isOperator(client)) {
		client->sendMessage(RPL::makeReply(S_ERR_CHANOPRIVSNEEDED, "<>", errMap));
		return ERR_CHANOPRIVSNEEDED;
	}
	chan->setSubject(params.footer);

	#ifdef SHOW_FUNC
	DG();
	#endif
	return (RPL_TOPIC);
}

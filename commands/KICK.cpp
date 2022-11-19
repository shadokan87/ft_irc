/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu.escande@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:51:25 by matthieu          #+#    #+#             */
/*   Updated: 2022/04/27 10:59:00 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"
/* Commande: KICK */
/* Paramètres: <canal> <utilisateur> [<commentaire>] */

/* La commande KICK est utilisée pour retirer par la force un utilisateur d'un canal (PART forcé). */
/* Seul un opérateur de canal peut kicker un autre utilisateur hors d'un canal. Tout serveur qui reçoit un message KICK vérifie si le message est valide (c'est-à-dire si l'expéditeur est bien un opérateur du canal) avant d'ôter la victime du canal. */

/* Réponses numériques : */
/*            ERR_NEEDMOREPARAMS              ERR_NOSUCHCHANNEL */
/*            ERR_BADCHANMASK                 ERR_CHANOPRIVSNEEDED */
/*            ERR_NOTONCHANNEL */

/* Exemples: */
/*		KICK &Melbourne Matthew ; Kick Matthew de &Melbourne */
/*		KICK #Finnish John :Speaking English ; Kick John de #Finnish en spécifiant "Speaking English" comme raison (commentaire). */
/*		:WiZ KICK #Finnish John ; Message KICK de WiZ pour retirer John du canal #Finnish */

COMMAND_RET_VAL KICK(COMMAND_PARAM)
{
	std::map<std::string, Channel*> _channels = srv.getChannels();
	std::vector<std::string> p = params.parameters;
	std::map<std::string, std::string> errMap;
	{
		errMap["commande"] = params.command_name;
		errMap["UserID"] = client->getInfo().nick;
		errMap["server"] = SERVER_NAME;
	}
	if (p.size() != 2) {
		client->sendMessage(RPL::makeReply(S_ERR_NEEDMOREPARAMS, "<>", errMap));
		return ERR_NEEDMOREPARAMS;
	}
	std::string name = p[0];
	if (_channels.find(name) == _channels.end()) {
		client->sendMessage(RPL::makeReply(S_ERR_NOSUCHCHANNEL, "<>", errMap));
		return ERR_NOSUCHCHANNEL;
	}
	if (!_channels[name]->isOperator(client)) {
		client->sendMessage(RPL::makeReply(S_ERR_CHANOPRIVSNEEDED, "<>", errMap));
		return ERR_CHANOPRIVSNEEDED;
	}
	if (!_channels[name]->getClient(p[1])) {
		client->sendMessage(RPL::makeReply(S_ERR_NOTONCHANNEL, "<>", errMap));
		return ERR_NOTONCHANNEL;
	}
	PART(params, _channels[name]->getClient(p[1]), srv);
	#ifdef SHOW_FUNC
	DG();
	#endif
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LIST.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu.escande@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:03:48 by matthieu          #+#    #+#             */
/*   Updated: 2022/04/27 10:58:55 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"
// http://abcdrfc.free.fr/rfc-vf/rfc1459.html#426

// Commande: LIST
// Paramètres: [<canal>{,<canal>} [<serveur>]]

// Le message LIST est utilisé pour lister les canaux et leur sujet. Si le paramètre <canal> est utilisé, seul le statut de ces canaux est affiché. Les canaux privés sont listés (sans leur sujet) comme canal "Prv" à moins que le client qui génère la requête soit effectivement sur le canal. De même, les canaux secrets ne sont pas listés du tout, à moins que le client soit un membre du canal en question.

// Réponses numériques :

//            ERR_NOSUCHSERVER                RPL_LISTSTART
//            RPL_LIST                        RPL_LISTEND

// Exemples:
//		LIST ; Liste tous les canaux.
//		LIST #twilight_zone,#42 ; Liste les canaux #twilight_zone et #42
COMMAND_RET_VAL LIST(COMMAND_PARAM)
{
	(void)client;
	COMMAND_RET_VAL ret = 0;
	std::map<std::string, Channel*> _channels = srv.getChannels();
	std::map<std::string, std::string> errMap;
	{
		errMap["commande"] = params.command_name;
		errMap["UserID"] = client->getInfo().nick;
		errMap["server"] = SERVER_NAME;
	}

	/* if (_channels.empty()) */
	/* 	return ret; */
	client->sendMessage(RPL::makeReply(S_RPL_LISTSTART, "<>",errMap));
	for (std::map<std::string, Channel *>::const_iterator it = _channels.begin(); it != _channels.end(); ++it) {
		if (!it->second->isSecret()) {
			errMap["canal"] = it->second->getName();
			errMap["sujet"] = it->second->getSubject();
			client->sendMessage(RPL::makeReply(S_RPL_LIST, "<>", errMap));
		}
	}
	client->sendMessage(RPL::makeReply(S_RPL_LISTEND, "<>",errMap));
	#ifdef SHOW_FUNC
	DG();
	#endif
	return (ret);
}

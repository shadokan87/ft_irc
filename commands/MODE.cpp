/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu.escande@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 15:01:46 by matthieu          #+#    #+#             */
/*   Updated: 2022/04/27 10:58:48 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "irc.hpp"

/*
 * http://abcdrfc.free.fr/rfc-vf/rfc1459.html#423
 */
/* Commande: MODE */

/* La commande MODE est une commande à utilisation duale sur IRC. Elle permet aussi bien de changer les modes des utilisateurs que ceux des canaux. La raison à ce choix est qu'un jour les pseudonymes deviendront obsolètes et la propriété équivalente sera le canal. */

/* Lors du traitement des messages MODE, il est recommandé de commencer par décomposer le message en entier, puis de réaliser les modifications résultantes. */




/* 4.2.3.1 Les modes des canaux */
/* Paramètres: <canal> {[+|-]|o|p|s|i|t|n|b|v} [<limite>] [<utilisateur>] [<masque de bannissement >] */

/* La commande MODE permet aux opérateurs de canal de changer les caractéristiques de 'leur' canal. Les serveurs doivent aussi pouvoir changer les modes du canal, de façon à pouvoir créer des opérateurs. */

/* Les modes disponibles pour les canaux sont les suivants : */
/* o - donne/retire les privilèges d'opérateur de canal */
/* p - drapeau de canal privé */
/* s - drapeau de canal secret */
/* i - drapeau de canal accessible uniquement sur invitation */
/* t - drapeau de sujet de canal modifiable uniquement par les opérateurs */
/* n - pas de messages dans un canal provenant de clients à l'extérieur du canal */
/* m - canal modéré */
/* l - définit le nombre maximal de personnes dans un canal */
/* b - définit un masque de bannissement pour interdire l'accès à des utilisateurs */
/* v - donne/retire la possibilité de parler dans un canal modéré */
/* k - définit la clé du canal (mot de passe) */

/* Lors de l'utilisation des options 'o' et 'b', le nombre de paramètres est restreint à trois par commande, et ce pour n'importe quelle combinaison de 'o' et de 'b'. */




/* 4.2.3.2 Modes des utilisateurs */
/* Paramètres: <pseudonyme> {[+|-]|i|w|s|o} */

/* Les modes utilisateurs sont typiquement des modifications qui affectent la façon dont le client est vu par les autres, ou quels types de messages sont reçus. Une commande MODE n'est acceptée que si l'expéditeur du message et le pseudonyme donné en paramètre sont les mêmes. */

/* Les modes disponibles sont : */
/* i - marque un utilisateur comme invisible ; */
/* s - marque un utilisateur comme recevant les notifications du serveur ; */
/* w - l'utilisateur reçoit les WALLOPs ; */
/* o - drapeau d'opérateur. */

/* D'autres modes seront disponibles plus tard. */

/* Si un utilisateur tente de devenir opérateur en utilisant le drapeau "+o", la tentative doit être ignorée. Par contre, il n'y a pas de restriction à ce que quelqu'un se 'deoppe' (en utilisant "-o"). */

/* Réponses numériques : */

/*            ERR_NEEDMOREPARAMS              RPL_CHANNELMODEIS */
/*            ERR_CHANOPRIVSNEEDED            ERR_NOSUCHNICK */
/*            ERR_NOTONCHANNEL                ERR_KEYSET */
/*            RPL_BANLIST                     RPL_ENDOFBANLIST */
/*            ERR_UNKNOWNMODE                 ERR_NOSUCHCHANNEL */

/*            ERR_USERSDONTMATCH              RPL_UMODEIS */
/*            ERR_UMODEUNKNOWNFLAG */





/* Exemples: */

/* Utilisation des modes de canal: */
/* MODE #Finnish +im ;			Rend le canal #Finnish modéré et 'uniquement sur invitation'. */
/* MODE #Finnish +o Kilroy ;	Donne le privilège de 'chanop' à Kilroy sur le canal #Finnish. */
/* MODE #Finnish +v Wiz ;		Autorise WiZ à parler sur #Finnish. */
/* MODE #Fins -s ;				Annule le drapeau 'secret' du canal #Fins. */
/* MODE #42 +k oulu ;			Définit la clé comme "oulu". */
/* MODE #eu-opers +l 10 ;		Définit le nombre maximal d'utilisateurs dans le canal à 10. */
/* MODE &oulu +b ;				Liste les masques de bannissement du canal. */
/* MODE &oulu +b *!*@* ;		Interdit à quiconque de venir sur le canal. */
/* MODE &oulu +b *!*@*.edu ;	Interdit à tout utilisateur dont le nom d'hôte correspond à *.edu d'accéder au canal. */

/* Utilisation des modes d'utilisateur : */
/* :MODE WiZ -w ;			supprime la réception des messages WALLOPS pour WiZ. */
/* :Angel MODE Angel +i ;	Message d'Angel pour se rendre invisible. */
/* MODE WiZ -o ;			WiZ se 'deoppe' (retire son statut d'opérateur). Le contraire ("MODE WiZ +o") ne doit pas être autorisé car cela court-circuiterait la commande OPER. */

static COMMAND_RET_VAL canalMode(COMMAND_PARAM, std::map<std::string, std::string> errMap) {
	std::vector<std::string> p = params.parameters;
	std::map<std::string, Channel*> _channels = srv.getChannels();
	std::string name = p[0];
	{
		errMap["nom de canal"] = name;
		errMap["canal"] = name;
	}

	if (_channels.find(name) == _channels.end()) {
		client->sendMessage(RPL::makeReply(S_ERR_NOSUCHCHANNEL, "<>", errMap));
		return ERR_NOSUCHCHANNEL;
	}
	Channel * chan = _channels[name];
	if (!client->inChan(chan)) {
		client->sendMessage(RPL::makeReply(S_ERR_NOTONCHANNEL, "<>", errMap));
		return ERR_NOTONCHANNEL;
	} if (!chan->isOperator(client)) {
		client->sendMessage(RPL::makeReply(S_ERR_CHANOPRIVSNEEDED, "<>", errMap));
		return ERR_CHANOPRIVSNEEDED;
	}
	bool	add = true;
	for (std::string::iterator it = p[1].begin(); it != p[1].end(); ++it) {
		if ((*it == '-' || *it == '+') && it == p[1].begin()) {
			add = (*it == '+');
		} else if (*it == 'o') {
			if (p.size() != 3) {
				client->sendMessage(RPL::makeReply(S_ERR_NEEDMOREPARAMS, "<>", errMap));
				return ERR_NEEDMOREPARAMS;
			}
			Client* c = chan->getClient(p[2]);
			if (c == NULL) {
				errMap["pseudonyme"] = p[2];
				client->sendMessage(RPL::makeReply(S_ERR_NOSUCHNICK, "<>", errMap));
				return ERR_NOSUCHNICK;
			}
			chan->addOperator(c);
		}
		else if (*it == 's') { chan->setSecret(add); }
		else if (*it == 't') { chan->setSubjectOp(add); }
		else if (*it == 'l') {
			if (p.size() < 3) {
				client->sendMessage(RPL::makeReply(S_ERR_NEEDMOREPARAMS, "<>", errMap));
				return ERR_NEEDMOREPARAMS;
			} else
				chan->setMaxClient(atoi(p[2].c_str()));
		} else if (*it == 'b') {
			if (p.size() != 3) {
				for (std::vector<std::string>::const_iterator it = chan->getBanMask().begin(); it != chan->getBanMask().end(); ++it) {
					errMap["banID"] = *it;
					client->sendMessage(RPL::makeReply(S_RPL_BANLIST, "<>", errMap));
				}
				client->sendMessage(RPL::makeReply(S_RPL_ENDOFBANLIST, "<>", errMap));
			}
			else
				chan->addBanMask(p[2]);
		} else if (*it == 'k') {
			if (!chan->isPasswordProtected()) {
				client->sendMessage(RPL::makeReply(S_ERR_KEYSET, "<>", errMap));
				return ERR_KEYSET;
			}
			if (p.size() != 3) {
				client->sendMessage(RPL::makeReply(S_ERR_NEEDMOREPARAMS, "<>", errMap));
				return ERR_NEEDMOREPARAMS;
			} else {
				chan->setPassword(p[2]);
				chan->setPasswordProtected(true);
			}
		} else {
			errMap["caractere"] = std::string(it, it+1);
			client->sendMessage(RPL::makeReply(S_ERR_UNKNOWNMODE, "<>", errMap));
			return ERR_UNKNOWNMODE;
		}
	}
	return 0;
}

static COMMAND_RET_VAL clientMode(COMMAND_PARAM, std::map<std::string, std::string> errMap) {
	std::vector<std::string> p = params.parameters;
	std::string name = p[0];

	if (client->getInfo().nick != p[0] && client->getInfo().username != p[0]) {
		client->sendMessage(RPL::makeReply(S_ERR_USERSDONTMATCH, "<>", errMap));
		return ERR_USERSDONTMATCH;
	}
	bool	add = true;
	for (std::string::iterator it = p[1].begin(); it != p[1].end(); ++it) {
		if ((*it == '-' || *it == '+') && it == p[1].begin()) {
			add = (*it == '+');
		} else if (*it == 'i') {
			client->setInvisible(add);
		} else if (*it == 'o') {
			if (!add) {
				std::map<std::string, Channel *> Channels = srv.getChannels();
				for (std::map<std::string, Channel *>::iterator it = Channels.begin(); it != srv.getChannels().end(); ++it) {
					it->second->removeOperator(client);
				}
			}
		} else {
			client->sendMessage(RPL::makeReply(S_ERR_UMODEUNKNOWNFLAG, "<>", errMap));
			return ERR_UMODEUNKNOWNFLAG;
		}
	}

	return 0;
}

COMMAND_RET_VAL MODE(COMMAND_PARAM) {
	std::map<std::string, std::string> errMap;
	COMMAND_RET_VAL ret;
	{
		errMap["commande"] = params.command_name;
		errMap["UserID"] = client->getInfo().nick;
		errMap["server"] = SERVER_NAME;
	}
	if (params.parameters.size() < 2) {
		client->sendMessage(RPL::makeReply(S_ERR_NEEDMOREPARAMS, "<>", errMap));
		return ERR_NEEDMOREPARAMS;
	}
	if (isChannelName(params.parameters[0])) {
		ret = canalMode(params, client, srv, errMap);
	} else {
		ret = clientMode(params, client, srv, errMap);
	}


	#ifdef SHOW_FUNC
	DG();
	#endif
	return (ret);
}

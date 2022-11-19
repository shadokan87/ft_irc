/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu.escande@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:07:10 by matthieu          #+#    #+#             */
/*   Updated: 2022/04/27 10:58:20 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"
/*
 * http://abcdrfc.free.fr/rfc-vf/rfc1459.html#412
 *
 * */
/* 4.1.2 Message NICK */
/* Commande : NICK */
/* Paramètres : <pseudonyme> [ <compteur de distance> ] */

/* Le message NICK est utilisé pour donner un pseudonyme à un utilisateur, ou pour changer le pseudonyme précédent. Le paramètre <compteur de distance> n'est utilisé que par les serveurs, et sert à indiquer quelle est la distance entre un utilisateur et son serveur local. Une connexion locale a un compteur de distance de zéro. Si un client fournit un compteur de distance, il doit être ignoré. */

/* Si un message NICK arrive à un serveur qui connaît déjà un autre client de pseudo identique, une collision de pseudonymes a lieu. Le résultat d'une collision de pseudonymes est la suppression de toutes les instances du pseudonyme de la base du serveur, et l'envoi d'un message KILL afin de retirer le pseudonyme des bases de données de tous les autres serveurs. Si le message NICK à l'origine de la collision de pseudonymes est un changement de pseudonyme, alors le pseudo originel (l'ancien) doit aussi être retiré. */

/* Si le serveur reçoit un NICK identique d'un client auquel il est connecté directement, il peut envoyer un ERR_NICKCOLLISION au client local, ignorer la commande NICK, et ne pas générer de KILLs. */

/* Réponses numériques : */
/*            ERR_NONICKNAMEGIVEN             ERR_ERRONEUSNICKNAME */
/*            ERR_NICKNAMEINUSE               ERR_NICKCOLLISION */
/* Exemples: */

/* NICK Wiz ; Ajout d'un nouveau pseudo "Wiz". */
/* :WiZ NICK Kilroy ; WiZ change son pseudo en Kilroy. */

/* [testnick](127.0.0.1) => :127.0.0.1 433 testnick :testnick :Nickname is already in use */
COMMAND_RET_VAL NICK(COMMAND_PARAM)
{
	(void)params;
	(void)client;
	(void)srv;
	COMMAND_RET_VAL ret = 0;
	#ifdef SHOW_FUNC
	std::cout << COLOR(YELLOW, __PRETTY_FUNCTION__) << std::endl;
	#endif
	std::map<int, Client*> Clients = srv.getClients();
	std::map<int, Client*>::iterator beg = Clients.begin();
	std::map<int, Client*>::iterator end = Clients.end();
	while (beg != end)
	{
		if ((*beg).second->getInfo().nick == params.parameters[0])
		{
			std::map<std::string, std::string> p;
			p.insert(std::make_pair("nick", params.parameters[0]));
			p["server"] = SERVER_NAME;
			client->sendMessage(RPL::makeReply(S_ERR_NICKNAMEINUSE, "<>", p));
			return (ret);
		}
		beg++;
	}
	client->getInfo().nick = params.parameters[0];
	return (ret);
}

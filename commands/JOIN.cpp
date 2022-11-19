/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu.escande@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 23:15:05 by matthieu          #+#    #+#             */
/*   Updated: 2022/04/27 10:59:12 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"
/*
 * http://abcdrfc.free.fr/rfc-vf/rfc1459.html#421
 *
 * */
// Commande: JOIN
// Paramètres: <canal>{,<canal>} [<clé>{,<clé>}]

// La commande JOIN est utilisée par un client pour commencer à écouter un canal spécifique. L'accès à un canal est autorisé ou non uniquement par le serveur auquel le client est connecté ; tous les autres serveurs ajoutent automatiquement l'utilisateur au canal quand la demande vient d'un autre serveur. Les conditions qui affectent ceci sont les suivantes :
// 1. L'utilisateur doit être invité si le canal est en mode "sur invitation seulement"
// 2. Le pseudo/nom d'utilisateur/nom d'hôte ne doit pas correspondre à un bannissement actif.
// 3. La bonne clé (mot de passe) doit être fournie si elle est définie.

// Ceci est discuté plus en détails dans la description de la commande MODE (voir la section 4.2.3 pour plus de détails).

// Une fois qu'un utilisateur a accès à un canal, il reçoit des notifications de toutes les commandes que son serveur reçoit et qui affectent le canal. Cela inclut MODE, KICK, PART, QUIT, et bien sûr PRIVMSG/NOTICE. La commande JOIN doit être diffusée à tous les serveurs du réseau pour qu'ils sachent où trouver qui est dans chaque canal. Cela permet une distribution optimale des messages PRIVMSG/NOTICE du canal.

// Si un JOIN a lieu avec succès, on envoie à l'utilisateur le sujet du canal (en utilisant RPL_TOPIC) et la liste des utilisateurs du canal (en utilisant RPL_NAMREPLY), y compris lui-même.

// Réponses numériques :
//            ERR_NEEDMOREPARAMS              ERR_BANNEDFROMCHAN
//            ERR_INVITEONLYCHAN              ERR_BADCHANNELKEY
//            ERR_CHANNELISFULL               ERR_BADCHANMASK
//            ERR_NOSUCHCHANNEL               ERR_TOOMANYCHANNELS
//            RPL_TOPIC

// Exemples:
//		JOIN #foobar ; accède au canal #foobar.
//		JOIN &foo fubar ; accède au canal &foo en utilisant la clé "fubar".
//		JOIN #foo,&bar fubar ; accède au canal #foo en utilisant la clé "fubar", et &bar en n'utilisant pas de clé.
//		JOIN #foo,#bar fubar,foobar ; accède au canal #foo en utilisant la clé "fubar", et au canal #bar en utilisant la clé "foobar".
//		JOIN #foo,#bar ; accède au canaux #foo and #bar.
//		:WiZ JOIN #Twilight_zone ; message JOIN de WiZ

bool	isChannelName(std::string name) {

	if (name[0] == '#' || name[0] == '&')
		return true;
	return false;
}

/* static void */

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
	p["commande"] = "JOIN";
	p["server"] = SERVER_NAME;
	for (std::map<int, Client*>::iterator beg = clients.begin(); beg != clients.end(); ++beg)
	{
		p["nick2"] = beg->second->getInfo().nick;
		client->sendMessage(RPL::makeReply(S_RPL_NAMEREPLY, "<>", p));
		beg->second->sendMessage(RPL::makeReply(S_RPL_KEEPINTOUCH, "<>", p));
	}
	//-c -p -w
	client->sendMessage(RPL::makeReply(S_RPL_ENDOFNAMES, "<>", p));
}

COMMAND_RET_VAL JOIN(COMMAND_PARAM)
{
	(void)srv;
	std::vector<std::string> p = params.parameters;
	std::map<std::string, Channel*> _channels = srv.getChannels();
	std::map<std::string, std::string> errMap;
	{
		errMap["commande"] = params.command_name;
		errMap["UserID"] = client->getInfo().nick;
		errMap["server"] = SERVER_NAME;
	}
	COMMAND_RET_VAL ret = 0;
	if (p.size() != 1) {
		client->sendMessage(RPL::makeReply(S_ERR_NEEDMOREPARAMS, "<>", errMap));
		return ERR_NEEDMOREPARAMS;
	}
	do {
		size_t chan_pos = p[0].find_first_of(',');
		std::string name = p[0].substr(0, chan_pos);
		if (chan_pos >= p[0].length()) {
			p[0].clear();
		} else {
			p[0] = p[0].substr(chan_pos+1);
		}
		std::string key = "";
		if (p.size() >= 2) {
			size_t keys_pos = p[1].find_first_of(',');
			key = p[1].substr(0, keys_pos);
			if (keys_pos >= p[1].length()) {
				p[1].clear();
			} else {
				p[1] = p[1].substr(keys_pos+1);
			}
		}
		{
			errMap["nom de canal"] = name;
			errMap["canal"] = name;
		}
		if (_channels.find(name) == _channels.end()) {
			if (!isChannelName(name)) {
				client->sendMessage(RPL::makeReply(S_ERR_NOSUCHCHANNEL, "<>", errMap));
				return ERR_NOSUCHCHANNEL;
			}
			params.srv->add_channel(client, name, key);
			_channels = params.srv->getChannels();
			client->sendMessage(RPL::makeReply(":<UserID> JOIN :<canal>", "<>", errMap));
			client->sendMessage(RPL::makeReply(":<Domain> <[RPL_TOPIC][1]> <NickName> <ChannelName> :<Topic>", "<>", errMap));
		} else {
			for (std::vector<std::string>::iterator it = _channels[name]->getBanMask().begin();
					it != _channels[name]->getBanMask().end(); ++it) {
				if (1) { //TODO verif if mask is good (`*!*@*' should ban everyone)
					client->sendMessage(RPL::makeReply(S_ERR_BANNEDFROMCHAN, "<>", errMap));
					return ERR_BANNEDFROMCHAN;
				}
			}
			if (_channels[name]->isPasswordProtected() && key != _channels[name]->getPassword()) {
				client->sendMessage(RPL::makeReply(S_ERR_BADCHANNELKEY, "<>", errMap));
				return ERR_BADCHANNELKEY;
			} if (client->isBannedFrom(_channels[name])) {
				client->sendMessage(RPL::makeReply(S_ERR_BANNEDFROMCHAN, "<>", errMap));
				return ERR_BANNEDFROMCHAN;
			} if (_channels[name]->addClient(client)) {
				client->sendMessage(RPL::makeReply(S_ERR_CHANNELISFULL, "<>", errMap));
				return ERR_CHANNELISFULL;
			}
		}
		if (client->joinChan(_channels[name])) {
			client->sendMessage(RPL::makeReply(S_ERR_TOOMANYCHANNELS, "<>", errMap));
			return ERR_TOOMANYCHANNELS;
		}
		reply(client, name, _channels);
	} while(!p[0].empty());
	#ifdef SHOW_FUNC
	std::cout << COLOR(YELLOW, __PRETTY_FUNCTION__) << std::endl;
	#endif
	return (ret);
}

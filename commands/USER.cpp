#include "irc.hpp"
/*
 * http://abcdrfc.free.fr/rfc-vf/rfc1459.html#413
 *
 * */
/* 4.1. Message USER */
/* Commande: USER */
/* Paramètres: <nom d'utilisateur> <hôte> <nom de serveur> <nom réel> */

/* Le message USER est utilisé au début d'une connexion pour spécifier le nom d'utilisateur, le nom d'hôte, le nom de serveur, et le véritable nom d'un nouvel utilisateur. Il est aussi utilisé lors de la communication entre les serveurs pour indiquer l'arrivée d'un nouvel utilisateur sur IRC, puisque c'est seulement après avoir envoyé et le USER et le NICK qu'un utilisateur devient enregistré. */

/* Entre serveurs, USER doit être préfixé du pseudonyme du client-> Notez que le nom d'hôte et le nom de serveur sont généralement ignorés par le serveur IRC quand la commande USER vient directement d'un client->(pour des raisons de sécurité), mais sont utilisés dans la communication de serveur à serveur. Cela signifie que NICK doit toujours être envoyé à un serveur distant quand un nouvel utilisateur est ajouté au reste du réseau, avant que le USER correspondant soit envoyé. */

/* Notez aussi que le paramètre 'vrai nom' doit être le dernier paramètre, car il peut contenir des espaces, et il doit être préfixé par deux points (':') de façon à être reconnu comme tel. */

/* Puisqu'il est facile pour un client->de mentir sur son nom si on se base uniquement sur le message USER, il est recommandé d'utiliser un "serveur d'identité". Si l'hôte dont l'utilisateur se connecte a un serveur de ce type activé, le nom d'utilisateur est défini par la réponse de ce "serveur d'identité". */

/* Réponses numériques : */

/*            ERR_NEEDMOREPARAMS              ERR_ALREADYREGISTRED */
/* Exemples: */

/* USER guest tolmoon tolsun :Ronnie Reagan ; Utilisateur s'enregistrant avec un nom d'utilisateur de "guest" et un vrai nom de "Ronnie Reagan". :testnick USER guest tolmoon tolsun :Ronnie Reagan ; message entre les serveurs contenant le pseudonyme à qui appartient la commande USER.3 */

COMMAND_RET_VAL USER(COMMAND_PARAM)
{
	(void)params;
	(void)client;
	(void)srv;
	COMMAND_RET_VAL ret = 0;
	#ifdef SHOW_FUNC
	std::cout << COLOR(YELLOW, __PRETTY_FUNCTION__) << std::endl;
	#endif
	std::map<std::string, std::string> p;
	p["server"] = SERVER_NAME;
	if (params.parameters.size() < 3)
	{
		p.insert(std::make_pair("server", SERVER_NAME));
		p.insert(std::make_pair("command", params.command_name));

		client->sendMessage(ERR::NEEDMOREPARAMS(p));
	}
	else if (client->getInfo().registred == false)
	{
		p.insert(std::make_pair("server", SERVER_NAME));
		p.insert(std::make_pair("nick", client->getInfo().nick));
		client->sendMessage(RPL::makeReply(S_ERR_ALREADYREGISTRED ,"<>", p));
	}
	else
	{  
		client->getInfo().username = params.parameters[0];
		client->getInfo().realname = params.footer;
		// test makeReply
		{
			std::map<std::string, std::string> WELCOME_P;
			std::map<std::string, std::string> YOURHOST_P;
			std::map<std::string, std::string> CREATED_P;
			std::map<std::string, std::string> MYINFO_P;
  			WELCOME_P["nick"] = client->getInfo().username;
			WELCOME_P["network"] = "network_name";
			WELCOME_P["server"] = SERVER_NAME;
	  
			YOURHOST_P["nick"] = client->getInfo().username;
			YOURHOST_P["username"] = client->getInfo().username;
			YOURHOST_P["version"] = "1.0";
			YOURHOST_P["server"] = SERVER_NAME;
			YOURHOST_P["servername"] = SERVER_NAME;
  			CREATED_P["nick"] = client->getInfo().username;
			CREATED_P["server"] = SERVER_NAME;
			CREATED_P["datetime"] = "11/08/1999";
  			MYINFO_P["nick"] = client->getInfo().username;
			MYINFO_P["server"] = SERVER_NAME;
			MYINFO_P["version"] = "1.0";
			MYINFO_P["available umodes"] = "rw";
			MYINFO_P["available cmodes"] = "rw";
  			client->sendMessage(RPL::makeReply(S_RPL_WELCOME, "<>", WELCOME_P));
			client->sendMessage(RPL::makeReply(S_RPL_YOURHOST, "<>", YOURHOST_P));
			client->sendMessage(RPL::makeReply(S_RPL_CREATED, "<>", CREATED_P));
			client->sendMessage(RPL::makeReply(S_RPL_MYINFO, "<>", MYINFO_P));
		}
	}
	return (ret);
}

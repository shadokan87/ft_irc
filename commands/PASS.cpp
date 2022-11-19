#include "irc.hpp"
/*
 * http://abcdrfc.free.fr/rfc-vf/rfc1459.html#411
 *
 * */
/* 4.1. Message PASS */
/* Commande : PASS */
/* Paramètres : <mot de passe> */

/* La commande PASS est utilisée pour définir le 'mot de passe de connexion'. Le mot de passe peut et doit être défini avant toute tentative de connexion. A l'heure actuelle, cela signifie que les clients doivent envoyer une commande PASS avant d'envoyer la combinaison NICK/USER, et que les serveurs doivent envoyer une commande PASS avant toute commande SERVER. Le mot de passe fourni doit correspondre à celui contenu dans les lignes C/N (pour les serveurs) ou dans les lignes I (pour les clients). Il est possible d'envoyer plusieurs commandes PASS avant de s'enregistrer, mais seule la dernière est utilisée pour la vérification, et elle ne peut plus changer une fois la connexion établie. */

/* Réponses numériques : */
/* ERR_NEEDMOREPARAMS              ERR_ALREADYREGISTRED */
/* Exemple: */
/* PASS motdepasssecretici1 */
/* error_message(ERR::ALREADYREGISTRED, { */
		/* 		client->sendMessage(ERR::ALREADYREGISTRED(client)) */
		/* 		}); */
		/* client->sendMessage(ERR::NEEDMOREPARAMS(client)); */
COMMAND_RET_VAL PASS(COMMAND_PARAM)
{
	COMMAND_RET_VAL ret = 0;
	#ifdef SHOW_FUNC
	std::cout << COLOR(YELLOW, __PRETTY_FUNCTION__) << std::endl;
	#endif
	std::map<std::string, std::string> p;
	{
		p["commande"] = params.command_name;
		p["UserID"] = client->getInfo().nick;
		p["server"] = SERVER_NAME;
	}
	if (client->getInfo().registred == true) {
		client->sendMessage(RPL::makeReply(S_ERR_ALREADYREGISTRED, "<>", p));
	}
	else if (!params.parameters.size()) {
		p.insert(std::make_pair("server", SERVER_NAME));
		p.insert(std::make_pair("command", params.command_name));
		client->sendMessage(ERR::NEEDMOREPARAMS(p));
	}
	else if (srv.testPassowrd(params.parameters[0]))
		client->getInfo().registred = true;
	return (ret);
}

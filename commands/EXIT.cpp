#include "irc.hpp"
/*
 * http://abcdrfc.free.fr/rfc-vf/rfc1459.html#416
 *
 * */
/* 4.1. Message QUIT */
/* Commande: QUIT */
/* Paramètres: [<Message de départ >] */

/* Une session de client->se termine par un message QUIT. Le serveur doit rompre la connexion avec le client->qui envoie un message QUIT. Si un <Message de départ> est fourni, il sera transmis au lieu du message par défaut, le pseudonyme. */

/* Lorsqu'une division réseau a lieu (déconnexion de deux serveurs), le message de départ est composé du nom des deux serveurs en cause, séparés par un espace. Le premier nom est celui du serveur toujours connecté, et le second, celui qui est désormais inaccessible. */

/* Si pour une autre raison, une connexion d'un client->est fermée sans que le client->ait envoyé de message QUIT (par exemple, le programme client->se termine, et une fin de fichier est envoyée sur la socket), le serveur doit remplir le message QUIT avec un message reflétant la nature de l'événement à l'origine de cette déconnexion. */

/* Réponses numériques: */
/*            Aucune. */
/* Exemples: */

/* QUIT :Parti déjeuner ; Format de message préféré.6 */
COMMAND_RET_VAL EXIT(COMMAND_PARAM)
{
	(void)params;
	(void)client;
	(void)srv;
	COMMAND_RET_VAL ret = 0;
	#ifdef SHOW_FUNC
	std::cout << COLOR(YELLOW, __PRETTY_FUNCTION__) << std::endl;
	#endif
	return (ret);
}

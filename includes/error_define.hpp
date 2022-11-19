/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_define.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu.escande@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 23:26:23 by matthieu          #+#    #+#             */
/*   Updated: 2022/04/27 10:52:35 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_DEFINE_HPP
#define ERROR_DEFINE_HPP

#define ERR_PREFIX "<username> <errno> <nick> :"

//Utilisé pour indiquer que le pseudonyme passé en paramètre à la commande n'est pas actuellement utilisé.
#define ERR_NOSUCHNICK 401 //"<pseudonyme> :No such nick/channel"
#define S_ERR_NOSUCHNICK ":<server> 401 <pseudonyme> :No such nick/channel"

//Utilisé pour indiquer que le nom du serveur donné n'existe pas actuellement.
#define ERR_NOSUCHSERVER 402 //"<nom de serveur> :No such server"
#define S_ERR_NOSUCHSERVER ":<server> <<nom de serveur> :No such server"

//Utilisé pour indiquer que le nom de canal donné est invalide.
#define ERR_NOSUCHCHANNEL 403 //"<nom de canal> :No such channel"
#define S_ERR_NOSUCHCHANNEL ":<server> 403 <nom de canal> :No such channel"

//Envoyé à un utilisateur qui (a) soit n'est pas dans un canal en mode +n ou (b) n'est pas opérateur (ou mode +v) sur un canal en mode +m ; et essaie d'envoyer un PRIVMSG à ce canal.
#define ERR_CANNOTSENDTOCHAN 404 //"<nom de canal> :Cannot send to channel"
#define S_ERR_CANNOTSENDTOCHAN ":<server> 404 <nom de canal> :Cannot send to channel"

//Envoyé à un utilisateur quand il a atteint le nombre maximal de canaux qu'il est autorisé à accéder simultanément, s'il essaie d'en rejoindre un autre.
#define ERR_TOOMANYCHANNELS 405 //"<nom de canal> :You have joined too many channels"
#define S_ERR_TOOMANYCHANNELS ":<server> 405 <nom de canal> :You have joined too many channels"

//Renvoyé par WHOWAS pour indiquer qu'il n'y a pas d'information dans l'historique concernant ce pseudonyme.
#define ERR_WASNOSUCHNICK 406 //"<nom de canal> :There was no such nickname"
#define S_ERR_WASNOSUCHNICK ":<server> 406 <nom de canal> :There was no such nickname"

//Renvoyé à un client qui essaie d'envoyer un PRIVMSG/NOTICE utilisant le format de destination utilisateur@hôte pour lequel utilisateur@hôte a plusieurs occurrences.
#define ERR_TOOMANYTARGETS 407 //"<destination> :Duplicate recipients. No message delivered"
#define S_ERR_TOOMANYTARGETS ":<server> 407 <destination> :Duplicate recipients. No message delivered"

//Message PING ou PONG sans le paramètre origine qui est obligatoire puisque ces commandes doivent marcher sans préfixe.
#define ERR_NOORIGIN 409 //":No origin specified"
#define S_ERR_NOORIGIN ":<server> 409 :No origin specified"

//Pas de destinataire.
#define ERR_NORECIPIENT 411 //":No recipient given (<commande>)"
#define S_ERR_NORECIPIENT ":<server> 411 :No recipient given (<commande>)"


//Les erreurs 412-414 sont renvoyées par PRIVMSG pour indiquer que le message n'a pas été délivré. ERR_NOTOPLEVEL et ERR_WILDTOPLEVEL sont les erreurs renvoyées lors d'une utilisation invalide de "PRIVMSG $<serveur>" ou de "PRIVMSG #<hôte>".
//Pas de texte à envoyer.
#define ERR_NOTEXTTOSEND 412 //":No text to send"
#define S_ERR_NOTEXTTOSEND ":<server> 412 :No text to send"
//Domaine principal non spécifié.
#define ERR_NOTOPLEVEL 413 //"<masque> :No toplevel domain specified"
#define S_ERR_NOTOPLEVEL ":<server> 413 <masque> :No toplevel domain specified"
//Joker dans le domaine principal
#define ERR_WILDTOPLEVEL 414 //"<masque> :Wildcard in toplevel domain"
#define S_ERR_WILDTOPLEVEL ":<server> 414 <masque> :Wildcard in toplevel domain"

//Renvoyé à un client enregistré pour indiquer que la commande envoyée est inconnue du serveur.
#define ERR_UNKNOWNCOMMAND 421 //"<commande> :Unknown command"
#define S_ERR_UNKNOWNCOMMAND ":<server> 421 <commande> :Unknown command"

//Le fichier MOTD du serveur n'a pas pu être ouvert.
#define ERR_NOMOTD 422 //":MOTD File is missing"
#define S_ERR_NOMOTD ":<server> 422 :MOTD File is missing"

//Renvoyé par un serveur en réponse à un message ADMIN quand il y a une erreur lors de la recherche des informations appropriées.
#define ERR_NOADMININFO 423 //"<serveur> :No administrative info available"
#define S_ERR_NOADMININFO ":<server> 423 <serveur> :No administrative info available"

//Message d'erreur générique utilisé pour rapporter un échec d'opération de fichier durant le traitement d'un message.
#define ERR_FILEERROR 424 //":File error doing <opération> on <fichier>"
#define S_ERR_FILEERROR ":<server> 424 :File error doing <opération> on <fichier>"

//Renvoyé quand un paramètre pseudonyme attendu pour une commande n'est pas fourni.
#define ERR_NONICKNAMEGIVEN 431 //":No nickname given"
#define S_ERR_NONICKNAMEGIVEN ":<server> 431 :No nickname given"

//Renvoyé après la réception d'un message NICK qui contient des caractères qui ne font pas partie du jeu autorisé. Voir les sections 1 et 2.2 pour les détails des pseudonymes valides.
#define ERR_ERRONEUSNICKNAME 432 //"<pseudo> :Erroneus nickname"
#define S_ERR_ERRONEUSNICKNAME(NICK) NICK + " :Erroneus nickname"

//Renvoyé quand le traitement d'un message NICK résulte en une tentative de changer de pseudonyme en un déjà existant.
#define ERR_NICKNAMEINUSE 433 //"<nick> :Nickname is already in use"
#define S_ERR_NICKNAMEINUSE ":<server> 433 <nick> :Nickname is already in use"

//Renvoyé par un serveur à un client lorsqu'il détecte une collision de pseudonymes (enregistrement d'un pseudonyme qui existe déjà sur un autre serveur).
#define ERR_NICKCOLLISION 436 //"<nick> :Nickname collision KILL"
#define S_ERR_NICKCOLLISION(NICK) NICK + " :Nickname collision KILL"

//Renvoyé par un serveur pour indiquer que l'utilisateur donné n'est pas dans le canal spécifié.
#define ERR_USERNOTINCHANNEL 441 //"<pseudo> <canal> :They aren't on that channel"
#define S_ERR_USERNOTINCHANNEL ":<server> 441 <pseudo> <canal> :They aren't on that channel"

//Renvoyé par le serveur quand un client essaie une commande affectant un canal dont il ne fait pas partie.
#define ERR_NOTONCHANNEL 442 //"<canal> :You're not on that channel"
#define S_ERR_NOTONCHANNEL ":<server> 442 <canal> :You're not on that channel"

//Renvoyé quand un client essaie d'inviter un utilisateur sur un canal où il est déjà.
#define ERR_USERONCHANNEL 443 //"<utilisateur> <channel> :is already on channel"
#define S_ERR_USERONCHANNEL ":<server> 443 <utilisateur> <channel> :is already on channel"

//Renvoyé par un SUMMON si la commande n'a pas pu être accomplie, car l'utilisateur n'est pas connecté.
#define ERR_NOLOGIN 444 //"<utilisateur> :User not logged in"
#define S_ERR_NOLOGIN ":<server> 444 <utilisateur> :User not logged in"

//Renvoyé en réponse à une commande SUMMON si le SUMMON est désactivé. Tout serveur qui ne gère pas les SUMMON doit retourner cette valeur.
#define ERR_SUMMONDISABLED 445 //":SUMMON has been disabled"
#define S_ERR_SUMMONDISABLED ":<server> 445 :SUMMON has been disabled"

//Retourné en réponse à une commande USERS si la commande est désactivée. Tout serveur qui ne gère pas les USERS doit retourner cette valeur.
#define ERR_USERSDISABLED 446 //":USERS has been disabled"
#define S_ERR_USERSDISABLED ":<server> 446 :USERS has been disabled"

//Retourné par le serveur pour indiquer à un client qu'il doit être enregistré avant que ses commandes soient traitées.
#define ERR_NOTREGISTERED 451 //":You have not registered"
#define S_ERR_NOTREGISTERED ":<server> 451 :You have not registered"

//Renvoyé par un serveur par de nombreuses commandes, afin d'indiquer que le client n'a pas fourni assez de paramètres.
#define ERR_NEEDMOREPARAMS 461 //"<commande> :Not enough parameters"
#define S_ERR_NEEDMOREPARAMS ":<server> 461 <commande> :Not enough parameters"
/* #define NEEDMOREPARAMS "<command> :Not enough parameters" */

//Retourné par le serveur à tout lien qui tente de changer les détails enregistrés (tels que mot de passe et détails utilisateur du second message USER)
#define ERR_ALREADYREGISTRED 462 //":You may not reregister"
#define S_ERR_ALREADYREGISTRED ":<server> 462 :You may not reregister"

//Renvoyé à un client qui essaie de s'enregistrer sur un serveur qui n'accepte pas les connexions depuis cet hôte.
#define ERR_NOPERMFORHOST 463 //":Your host isn't among the privileged"
#define S_ERR_NOPERMFORHOST ":<server> 463 :Your host isn't among the privileged"

//Retourné pour indiquer l'échec d'une tentative d'enregistrement d'une connexion dû à un mot de passe incorrect ou manquant.
#define ERR_PASSWDMISMATCH 464 //":Password incorrect"
#define S_ERR_PASSWDMISMATCH ":<server> 464 :Password incorrect"

//Retourné après une tentative de connexion et d'enregistrement sur un serveur configuré explicitement pour vous refuser les connexions.
#define ERR_YOUREBANNEDCREEP 465 //":You are banned from this server"
#define S_ERR_YOUREBANNEDCREEP ":<server> 465 :You are banned from this server"

//Clé de canal déjà définie.
#define ERR_KEYSET 467 //"<canal> :Channel key already set"
#define S_ERR_KEYSET ":<server> 467 <canal> :Channel key already set"

//Impossible de joindre le canal (+l)
#define ERR_CHANNELISFULL 471 //"<canal> :Cannot join channel (+l)"
#define S_ERR_CHANNELISFULL ":<server> 471 <canal> :Cannot join channel (+l)"

//Mode inconnu.
#define ERR_UNKNOWNMODE 472 //"<caractère> :is unknown mode char to me"
#define S_ERR_UNKNOWNMODE ":<server> 472 <caractere> :is unknown mode char to me"

//Impossible de joindre le canal (+i).
#define ERR_INVITEONLYCHAN 473 //"<canal> :Cannot join channel (+i)"
#define S_ERR_INVITEONLYCHAN ":<server> 473 <canal> :Cannot join channel (+i)"

//Impossible de joindre le canal (+b).
#define ERR_BANNEDFROMCHAN 474 //"<canal> :Cannot join channel (+b)"
#define S_ERR_BANNEDFROMCHAN ":<server> 474 <canal> :Cannot join channel (+b)"

//Impossible de joindre le canal (+k).
#define ERR_BADCHANNELKEY 475 //"<canal> :Cannot join channel (+k)"
#define S_ERR_BADCHANNELKEY ":<server> 475 <canal> :Cannot join channel (+k)"

//Toute commande qui requiert le privilège d'opérateur pour opérer doit retourner cette erreur pour indiquer son échec.
#define ERR_NOPRIVILEGES 481 //":Permission Denied- You're not an IRC operator"
#define S_ERR_NOPRIVILEGES ":<server> 481 :Permission Denied- You're not an IRC operator"

//Toute commande qui requiert les privilèges 'chanop' (tels les messages MODE) doit retourner ce message à un client qui l'utilise sans être chanop sur le canal spécifié.
#define ERR_CHANOPRIVSNEEDED 482 //"<canal> :You're not channel operator"
#define S_ERR_CHANOPRIVSNEEDED ":<server> 482 <canal> :You're not channel operator"

//Toute tentative d'utiliser la commande KILL sur un serveur doit être refusée et cette erreur renvoyée directement au client.
#define ERR_CANTKILLSERVER 483 //":You cant kill a server!"
#define S_ERR_CANTKILLSERVER ":<server> 483 :You cant kill a server!"

//Si un client envoie un message OPER et que le serveur n'a pas été configuré pour autoriser les connexions d'opérateurs de cet hôte, cette erreur doit être retournée.
#define ERR_NOOPERHOST 491 //":No O-lines for your host"
#define S_ERR_NOOPERHOST ":<server> 491 :No O-lines for your host"

//Renvoyé par un serveur pour indiquer que le message MODE a été envoyé avec un pseudonyme et que le mode spécifié n'a pas été identifié.
#define ERR_UMODEUNKNOWNFLAG 501 //":Unknown MODE flag"
#define S_ERR_UMODEUNKNOWNFLAG ":<server> 501 :Unknown MODE flag"

//Erreur envoyée à tout utilisateur qui essaie de voir ou de modifier le mode utilisateur d'un autre client.
#define ERR_USERSDONTMATCH 502 //":Cant change mode for other users"
#define S_ERR_USERSDONTMATCH ":<server> 502 :Cant change mode for other users"

#endif

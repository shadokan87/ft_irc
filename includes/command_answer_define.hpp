/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_answer_define.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu.escande@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 23:38:24 by matthieu          #+#    #+#             */
/*   Updated: 2022/04/26 10:22:04 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_ANSWER_DEFINE_HPP
#define COMMAND_ANSWER_DEFINE_HPP

#define S_RPL_KEEPINTOUCH ":<nick>!<username>@<hostname> <commande> <channel>"

#define RPL_NONE 300
// Numéro de réponse bidon. Inutilisé.

#define RPL_WELCOME 1
#define S_RPL_WELCOME ":<server> 001 <nick> :Welcome to the <network> Network, <nick>[!<user>@<host>]"
#define RPL_YOURHOST 2
#define S_RPL_YOURHOST ":<server> 002 <nick> :Your host is <servername>, running version <version>"
#define RPL_CREATED 3
#define S_RPL_CREATED ":<server> 003 <nick> :This server was created <datetime>"
#define RPL_MYINFO 4
#define S_RPL_MYINFO ":<server> 004 <nick> <servername> <version> <available umodes> <available cmodes> [<cmodes with param>]"
#define RPL_USERHOST 302 // ":[<réponse>{<espace><réponse>}]"
#define S_RPL_USERHOST ":[<réponse>{<espace><réponse>}]"
// Format de réponse utilisé par USERHOST pour lister les réponses à la liste des requêtes. La chaîne de réponse est composée ainsi :
// <réponse> ::= <pseudo>['*'] '=' <'+'|'-'><hôte>
// Le '*' indique si le client est enregistré comme opérateur. Les caractères '-' ou '+' indiquent respectivement si le client a défini un message AWAY ou non.

#define RPL_ISON 303 // ":[<pseudo> {<espace><pseudo>}]"
#define S_RPL_ISON ":[<pseudo> {<espace><pseudo>}]"
// Format de réponse utilisé par ISON pour lister les réponses à la liste de requête.

#define RPL_AWAY 301 // "<pseudo> :<message d'absence>"
#define S_RPL_AWAY "<pseudo> :<message d'absence>"
#define RPL_UNAWAY 305 // ":You are no longer marked as being away"
#define S_RPL_UNAWAY ":You are no longer marked as being away"
#define RPL_NOWAWAY 306 // ":You have been marked as being away"
#define S_RPL_NOWAWAY ":You have been marked as being away"
// Ces trois réponses sont utilisées avec la commande AWAY (si elle est autorisée). RPL_AWAY est envoyé à tout client qui envoie un PRIVMSG à un client absent. RPL_AWAY n'est envoyé que par le serveur sur lequel le client est connecté. Les réponses RPL_UNAWAY et RPL_NOWAWAY sont envoyées quand un client retire et définit un message AWAY.
#define RPL_WHOISUSER 311 // "<pseudo> <utilisateur> <hôte> * :<vrai nom>"
#define S_RPL_WHOISUSER "<pseudo> <utilisateur> <hôte> * :<vrai nom>"
#define RPL_WHOISSERVER 312 // "<pseudo> <serveur> :<info serveur>"
#define S_RPL_WHOISSERVER "<pseudo> <serveur> :<info serveur>"
#define RPL_WHOISOPERATOR 313 // "<pseudo> :is an IRC operator"
#define S_RPL_WHOISOPERATOR "<pseudo> :is an IRC operator"
#define RPL_WHOISIDLE 317 // "<pseudo> <integer> :seconds idle"
#define S_RPL_WHOISIDLE "<pseudo> <integer> :seconds idle"
#define RPL_ENDOFWHOIS 318 // "<pseudo> :End of /WHOIS list"
#define S_RPL_ENDOFWHOIS "<pseudo> :End of /WHOIS list"
#define RPL_WHOISCHANNELS 319 // "<pseudo> :{[@|+]<canal><espace>}"
#define S_RPL_WHOISCHANNELS "<pseudo> :{[@|+]<canal><espace>}"
// Les réponses 311 à 313 et 317 à 319 sont toutes générées en réponse à un message WHOIS. S'il y a assez de paramètres, le serveur répondant doit soit formuler une réponse parmi les numéros ci-dessus (si le pseudo recherché a été trouvé) ou renvoyer un message d'erreur. Le '*' dans RPL_WHOISUSER est là en tant que littéral et non en tant que joker. Pour chaque jeu de réponses, seul RPL_WHOISCHANNELS peut apparaître plusieurs fois (pour les longues listes de noms de canaux). Les caractères '@' et '+' à côté du nom de canal indiquent si un client est opérateur de canal, ou si on l'a autorisé à parler dans un canal modéré. La réponse RPL_ENDOFWHOIS est utilisée pour marquer la fin de la réponse WHOIS.

#define RPL_WHOWASUSER 314 // "<pseudo> <utilisateur> <hôte> * :<vrai nom>"
#define S_RPL_WHOWASUSER "<pseudo> <utilisateur> <hôte> * :<vrai nom>"
#define RPL_ENDOFWHOWAS 369 // "<pseudo> :End of WHOWAS"
#define S_RPL_ENDOFWHOWAS "<pseudo> :End of WHOWAS"
// Lorsqu'il répond à un message WHOWAS, un serveur doit utiliser RPL_WHOWASUSER, RPL_WHOISSERVER ou ERR_WASNOSUCHNICK pour chacun des pseudonymes de la liste fournie. A la fin de toutes les réponses, il doit y avoir un RPL_ENDOFWHOWAS (même s'il n'y a eu qu'une réponse, et que c'était une erreur).

#define RPL_LISTSTART 321 // "Channel :Users Name"
#define S_RPL_LISTSTART "Channel :Users Name"
#define RPL_LIST 322 // "<canal> <# visible> :<sujet>"
#define S_RPL_LIST "<canal> <# visible> :<sujet>"
#define RPL_LISTEND 323 // ":End of /LIST"
#define S_RPL_LISTEND ":End of /LIST"
// Les réponses RPL_LISTSTART, RPL_LIST, RPL_LISTEND marquent le début, les réponses proprement dites, et la fin du traitement d'une commande LIST. S'il n'y a aucun canal disponible, seules les réponses de début et de fin sont envoyées.
#define RPL_CHANNELMODEIS 324 // "<canal> <mode> <paramètres de mode>"
#define S_RPL_CHANNELMODEIS "<canal> <mode> <paramètres de mode>"
#define RPL_NOTOPIC 331 // "<canal> :No topic is set"
#define S_RPL_NOTOPIC "<canal> :No topic is set"
#define RPL_TOPIC 332 // "<canal> :<sujet>"
#define S_RPL_TOPIC "<canal> :<sujet>"
// Lors de l'envoi d'un message TOPIC pour déterminer le sujet d'un canal, une de ces deux réponses est envoyée. Si le sujet est défini, RPL_TOPIC est renvoyée, sinon c'est RPL_NOTOPIC.
#define RPL_INVITING 341 // "<canal> <pseudo>"
#define S_RPL_INVITING "<canal> <pseudo>"
// Renvoyé par un serveur pour indiquer que le message INVITE a été enregistré, et est en cours de transmission au client final.
#define RPL_SUMMONING 342 // "<utilisateur> :Summoning user to IRC"
#define S_RPL_SUMMONING "<utilisateur> :Summoning user to IRC"
// Renvoyé par un serveur en réponse à un message SUMMON pour indiquer qu'il appelle cet utilisateur.

#define RPL_VERSION 351 // "<version>.<debuglevel> <serveur> :<commentaires>"
#define S_RPL_VERSION "<version>.<debuglevel> <serveur> :<commentaires>"
// Réponse du serveur indiquant les détails de sa version. <version> est la version actuelle du programme utilisé (comprenant le numéro de mise à jour) et <debuglevel> est utilisé pour indiquer si le serveur fonctionne en mode débugage.
// Le champ <commentaire> peut contenir n'importe quel commentaire au sujet de la version, ou des détails supplémentaires sur la version.
#define RPL_WHOREPLY 352 // "<canal> <utilisateur> <hôte> <serveur> <pseudo> <H|G>[*][@|+] :<compteur de distance> <vrai nom>"
#define S_RPL_WHOREPLY "<canal> <utilisateur> <hôte> <serveur> <pseudo> <H|G>[*][@|+] :<compteur de distance> <vrai nom>"
#define RPL_ENDOFWHO 315 // "<nom> :End of /WHO list"
#define S_RPL_ENDOFWHO "<nom> :End of /WHO list"
// La paire RPL_WHOREPLY et RPL_ENDOFWHO est utilisée en réponse à un message WHO. Le RPL_WHOREPLY n'est envoyé que s'il y a une correspondance à la requête WHO. S'il y a une liste de paramètres fournie avec le message WHO, un RPL_ENDOFWHO doit être envoyé après le traitement de chaque élément de la liste, <nom> étant l'élément.

#define RPL_NAMEREPLY 353 // "<canal> :[[@|+]<pseudo> [[@|+]<pseudo> [...]]]"
#define S_RPL_NAMEREPLY "<nick>!<username>@<username> JOIN <nick2> :<channel>"
#define RPL_ENDOFNAMES 366 // "<canal> :End of /NAMES list"
#define S_RPL_ENDOFNAMES ":<server> 366 <nick> :<channel> :End of /NAMES list"
// En réponse à un message NAMES, une paire consistant de RPL_NAMREPLY et RPL_ENDOFNAMES est renvoyée par le serveur au client. S'il n'y a pas de canal résultant de la requête, seul RPL_ENDOFNAMES est retourné. L'exception à cela est lorsqu'un message NAMES est envoyé sans paramètre et que tous les canaux et contenus visibles sont renvoyés en une suite de message RPL_NAMEREPLY avec un RPL_ENDOFNAMES indiquant la fin.

#define RPL_LINKS 364 // "<masque> <serveur> :<compteur de distance> <info serveur>"
#define S_RPL_LINKS "<masque> <serveur> :<compteur de distance> <info serveur>"
#define RPL_ENDOFLINKS 365 // "<mask> :End of /LINKS list"
#define S_RPL_ENDOFLINKS "<mask> :End of /LINKS list"
// En réponse à un message LINKS, un serveur doit répondre en utilisant le nombre RPL_LINKS, et indiquer la fin de la liste avec une réponse RPL_ENDOFLINKS.
#define RPL_BANLIST 367 // "<canal> <identification de bannissement>"
#define S_RPL_BANLIST "<canal> <banID>"
#define RPL_ENDOFBANLIST 368 // "<canal> :End of channel ban list"
#define S_RPL_ENDOFBANLIST "<canal> :End of channel ban list"
// Quand il liste les bannissements actifs pour un canal donné, un serveur doit renvoyer la liste en utilisant les messages RPL_BANLIST et RPL_ENDOFBANLIST. Un RPL_BANLIST différent doit être utilisé pour chaque identification de bannissement. Après avoir listé les identifications de bannissement (s'il y en a), un RPL_ENDOFBANLIST doit être renvoyé.

#define RPL_INFO 371 // ":<chaîne>"
#define S_RPL_INFO ":<chaîne>"
#define RPL_ENDOFINFO 374 // ":End of /INFO list"
#define S_RPL_ENDOFINFO ":End of /INFO list"
// Un serveur répondant à un message INFO doit envoyer toute sa série d'info en une suite de réponses RPL_INFO, avec un RPL_ENDOFINFO pour indiquer la fin des réponses.

#define RPL_MOTDSTART 375 // ":- <serveur> Message of the day - "
#define S_RPL_MOTDSTART ":- <serveur> Message of the day - "
#define RPL_MOTD 372 // ":- <texte>"
#define S_RPL_MOTD ":- <texte>"
#define RPL_ENDOFMOTD 376 // ":End of /MOTD command"
#define S_RPL_ENDOFMOTD ":End of /MOTD command"
// Lorsqu'il répond à un message MOTD et que le fichier MOTD est trouvé, le fichier est affiché ligne par ligne, chaque ligne ne devant pas dépasser 80 caractères, en utilisant des réponses au format RPL_MOTD. Celles-ci doivent être encadrées par un RPL_MOTDSTART (avant les RPL_MOTDs) et un RPL_ENDOFMOTD (après).

#define RPL_YOUREOPER 381 // ":You are now an IRC operator"
#define S_RPL_YOUREOPER ":You are now an IRC operator"
// RPL_YOUREOPER est renvoyé à un client qui vient d'émettre un message OPER et a obtenu le statut d'opérateur.

#define RPL_REHASHING 382 // "<fichier de configuration> :Rehashing"
#define S_RPL_REHASHING "<fichier de configuration> :Rehashing"
// Si l'option REHASH est activée et qu'un opérateur envoie un message REHASH, un RPL_REHASHING est renvoyé à l'opérateur.

#define RPL_TIME 391 // "<serveur> :<chaîne indiquant l'heure locale du serveur>"
#define S_RPL_TIME "<serveur> :<chaîne indiquant l'heure locale du serveur>"
// Lorsqu'il répond à un message TIME, un serveur doit répondre en utilisant le format RPL_TIME ci-dessus. La chaîne montrant l'heure ne doit contenir que le jour et l'heure corrects. Il n'y a pas d'obligation supplémentaire.

#define RPL_USERSSTART 392 // ":UserID Terminal Hôte"
#define S_RPL_USERSSTART ":UserID Terminal Hôte"
#define RPL_USERS 393 // ":%-8s %-9s %-8s"
#define S_RPL_USERS ":%-8s %-9s %-8s"
#define RPL_ENDOFUSERS 394 // ":End of users"
#define S_RPL_ENDOFUSERS ":End of users"
#define RPL_NOUSERS 395 // ":Nobody logged in"
#define S_RPL_NOUSERS ":Nobody logged in"
// Si le message USERS est géré par un serveur, les réponses RPL_USERSTART, RPL_USERS, RPL_ENDOFUSERS et RPL_NOUSERS sont utilisées. RPL_USERSSTART doit être envoyé en premier, suivi par soit une séquence de RPL_USERS soit un unique RPL_NOUSER. Enfin, vient un RPL_ENDOFUSERS.

#define RPL_TRACELINK 200 // "Link <version & niveau de débugage> <destination> <serveur suivant>"
#define S_RPL_TRACELINK "Link <version & niveau de débugage> <destination> <serveur suivant>"
#define RPL_TRACECONNECTING 201 // "Try. <classe> <serveur>"
#define S_RPL_TRACECONNECTING "Try. <classe> <serveur>"
#define RPL_TRACEHANDSHAKE 202 // "H.S. <classe> <serveur>"
#define S_RPL_TRACEHANDSHAKE "H.S. <classe> <serveur>"
#define RPL_TRACEUNKNOWN 203 // "???? <classe> [<adresse IP du client au format utilisant des points>]"
#define S_RPL_TRACEUNKNOWN "???? <classe> [<adresse IP du client au format utilisant des points>]"
#define RPL_TRACEOPERATOR 204 // "Oper <classe> <pseudo>"
#define S_RPL_TRACEOPERATOR "Oper <classe> <pseudo>"
#define RPL_TRACEUSER 205 // "User <classe> <pseudo>"
#define S_RPL_TRACEUSER "User <classe> <pseudo>"
#define RPL_TRACESERVER 206 // "Serv <classe> <int>S <int>C <serveur> <pseudo!utilisateur|*!*>@<hôte|serveur>"
#define S_RPL_TRACESERVER "Serv <classe> <int>S <int>C <serveur> <pseudo!utilisateur|*!*>@<hôte|serveur>"
#define RPL_TRACENEWTYPE 208 // "<nouveau type> 0 <nom du client>"
#define S_RPL_TRACENEWTYPE "<nouveau type> 0 <nom du client>"
#define RPL_TRACELOG 261 // "File <fichier log> <niveau de débugage>"
#define S_RPL_TRACELOG "File <fichier log> <niveau de débugage>"
// Les RPL_TRACE* sont tous renvoyés par le serveur en réponse à un message TRACE. Le nombre de messages retournés dépend de la nature du message TRACE, et s'il a été envoyé par un opérateur ou non. Il n'y a pas d'ordre définissant lequel doit être le premier. Les réponses RPL_TRACEUNKNOWN, RPL_TRACECONNECTING et RPL_TRACEHANDSHAKE sont toutes utilisées pour des connexions qui n'ont pas été complètement établies, et sont soit inconnues, soit toujours en cours de connexion, soit dans la phase terminale de la 'poignée de main du serveur'. RPL_TRACELINK est envoyé par tout serveur qui traite un message TRACE et doit le transmettre à un autre serveur. La liste de RPL_TRACELINK envoyée en réponse à une commande TRACE traversant le réseau IRC devrait refléter la connectivité actuelle des serveurs le long du chemin. RPL_TRACENEWTYPE est utilisé pour toute connexion qui n'entre pas dans les autres catégories, mais qui est néanmoins affichée.

#define RPL_STATSLINKINFO 211 // "<nom du lien> <sendq> <messages envoyés> <octets envoyés> <message reçus> <octets reçus> <temps de connexion>"
#define S_RPL_STATSLINKINFO "<nom du lien> <sendq> <messages envoyés> <octets envoyés> <message reçus> <octets reçus> <temps de connexion>"
#define RPL_STATSCOMMANDS 212 // "<commande> <compteur>"
#define S_RPL_STATSCOMMANDS "<commande> <compteur>"
#define RPL_STATSCLINE 213 // "C <hôte> * <nom> <port> <classe>"
#define S_RPL_STATSCLINE "C <hôte> * <nom> <port> <classe>"
#define RPL_STATSNLINE 214 // "N <hôte> * <nom> <port> <classe>"
#define S_RPL_STATSNLINE "N <hôte> * <nom> <port> <classe>"
#define RPL_STATSILINE 215 // "I <hôte> * <hôte> <port> <classe>"
#define S_RPL_STATSILINE "I <hôte> * <hôte> <port> <classe>"
#define RPL_STATSKLINE 216 // "K <hôte> * <nom d'utilisateur> <port> <classe>"
#define S_RPL_STATSKLINE "K <hôte> * <nom d'utilisateur> <port> <classe>"
#define RPL_STATSYLINE 218 // "Y <classe> <fréquence des PINGS> <fréquence de connexion> <sendq max>"
#define S_RPL_STATSYLINE "Y <classe> <fréquence des PINGS> <fréquence de connexion> <sendq max>"
#define RPL_ENDOFSTATS 219 // "<lettre de stats> :End of /STATS report"
#define S_RPL_ENDOFSTATS "<lettre de stats> :End of /STATS report"
#define RPL_STATSLLINE 241 // "L <masque d'hôte> * <nom de serveur> <profondeur maxi>"
#define S_RPL_STATSLLINE "L <masque d'hôte> * <nom de serveur> <profondeur maxi>"
#define RPL_STATSUPTIME 242 // ":Server Up %d days %d:%02d:%02d"
#define S_RPL_STATSUPTIME ":Server Up %d days %d:%02d:%02d"
#define RPL_STATSOLINE 243 // "O <masque d'hôte> * <nom>"
#define S_RPL_STATSOLINE "O <masque d'hôte> * <nom>"
#define RPL_STATSHLINE 244 // "H <masque d'hôte> * <nom de serveur>"
#define S_RPL_STATSHLINE "H <masque d'hôte> * <nom de serveur>"
#define RPL_UMODEIS 221 // "<chaîne de mode utilisateur>"
#define S_RPL_UMODEIS "<chaîne de mode utilisateur>"
// Pour répondre à une requête au sujet du mode du client, RPL_UMODEIS est renvoyé.
#define RPL_LUSERCLIENT 251 // ":There are <entier> users and <entier> invisible on <entier> servers"
#define S_RPL_LUSERCLIENT ":There are <entier> users and <entier> invisible on <entier> servers"
#define RPL_LUSEROP 252 // "<entier> :operator(s) online"
#define S_RPL_LUSEROP "<entier> :operator(s) online"
#define RPL_LUSERUNKNOWN 253 // "<entier> :unknown connection(s)"
#define S_RPL_LUSERUNKNOWN "<entier> :unknown connection(s)"
#define RPL_LUSERCHANNELS 254 // "<entier> :channels formed"
#define S_RPL_LUSERCHANNELS "<entier> :channels formed"
#define RPL_LUSERME 255 // ":I have <entier> clients and <integer> servers"
#define S_RPL_LUSERME ":I have <entier> clients and <integer> servers"
// Lors du traitement d'un message LUSERS, le serveur envoie un lot de réponses parmi RPL_LUSERCLIENT, RPL_LUSEROP, RPL_USERUNKNOWN, RPL_LUSERCHANNELS et RPL_LUSERME. Lorsqu'il répond, un serveur doit envoyer RPL_LUSERCLIENT et RPL_LUSERME. Les autres réponses ne sont renvoyées que si le nombre trouvé n'est pas nul.

#define RPL_ADMINME 256 // "<serveur> :Administrative info"
#define S_RPL_ADMINME "<serveur> :Administrative info"
#define RPL_ADMINLOC1 257 // ":<info admin>"
#define S_RPL_ADMINLOC1 ":<info admin>"
#define RPL_ADMINLOC2 258 // ":<info admin>"
#define S_RPL_ADMINLOC2 ":<info admin>"
#define RPL_ADMINEMAIL 259 // ":<info admin>"
#define S_RPL_ADMINEMAIL ":<info admin>"
// Lorsqu'il répond à un message ADMIN, un serveur doit renvoyer les réponses RLP_ADMINME à RPL_ADMINEMAIL et fournir un texte de message avec chacune. Pour RPL_ADMINLOC1, on attend une description de la ville et de l'état où se trouve le serveur, suivie des détails de l'université et du département (RPL_ADMINLOC2), et finalement le contact administratif pour ce serveur (avec obligatoirement une adresse email) dans RPL_ADMINEMAIL.

#endif

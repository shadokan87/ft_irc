/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu.escande@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:58:55 by matthieu          #+#    #+#             */
/*   Updated: 2022/04/11 15:42:25 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

static int	safe_exit()
{
	return (1);
}

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		$print "Usage: <port> <password> (҂◡_◡)" << std::endl;
		return (1);
	}
	try{
		Server s(argv);
		s.init_server();
		s.run();
	}
	catch (const std::exception& e) {
		$print e.what() << "\n";
		return (safe_exit());
	}
	$print "Bye !";
	safe_exit();
	return (0);
}

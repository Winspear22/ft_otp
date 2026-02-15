/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adnen <adnen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 14:03:04 by adnen             #+#    #+#             */
/*   Updated: 2026/02/15 15:26:45 by adnen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.hpp"

int main(int argc, char **argv)
{
	if (argc != 3)
		return (ErrorInMain("ERROR: WRONG NUMBER OF ARGUMENTS: ", "Usage: " + std::string(argv[0]) + " <-k | -g> <secret>"));
	std::string args;
	args = argv[1];
	int res;
	int res2;

	res = args.compare("-k");
	res2 = args.compare("-g");

	if (res != 0 && res2 != 0)
		return (ErrorInMain("ERROR: WRONG ARGUMENT: ", "Usage: " + std::string(argv[0]) + " <-k | -g> <secret>"));
	std::cout << BOLD_GREEN << "SECRET: " << BOLD_WHITE << argv[2] << RESET
				<< std::endl;
	return (0);
}

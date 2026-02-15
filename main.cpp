/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adnen <adnen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 14:03:04 by adnen             #+#    #+#             */
/*   Updated: 2026/02/15 17:26:43 by adnen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OtpClass.hpp"
#include "includes.hpp"

int main(int argc, char **argv)
{
	if (argc != 3)
		return (ErrorsInMain("Error wrong number of arguments: ", "Usage: " + std::string(argv[0]) + " <-k | -g> <secret>"));
	std::string args;
	args = argv[1];
	int res;
	int res2;

	res = args.compare("-k");
	res2 = args.compare("-g");
				
	if (res != 0 && res2 != 0)
		return (ErrorsInMain("Error wrong argument: ", "Usage: " + std::string(argv[0]) + " <-k | -g> <secret>"));
	OtpClass otp;
	otp.setFlag(argv[1]);
	otp.readFile(argv[2]);
	return (0);
}

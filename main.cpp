/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adnen <adnen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 14:03:04 by adnen             #+#    #+#             */
/*   Updated: 2026/03/08 17:58:01 by adnen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OtpClass.hpp"
#include "includes.hpp"
#include <cstdlib>

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

	if (otp.getFlag() == "-g")
	{
		if (otp.readFile(argv[2]) == FAILURE)
			return (EXIT_FAILURE);
		otp.saveKey();
	}
	if (otp.getFlag() == "-k")
	{
		if (otp.readEncryptedFile(argv[2]) == FAILURE)
			return (EXIT_FAILURE);
		otp.generateOTP();
	}
	return (EXIT_SUCCESS);
}

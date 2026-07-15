/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 19:33:55 by adaloui           #+#    #+#             */
/*   Updated: 2026/07/15 21:23:23 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.hpp"
#include "ArgsParser.hpp"
#include "OtpClass.hpp"

int main(int argc, char **argv)
{
    if (ArgsParser::parseArguments(argc, argv) == FAILURE)
    {
        std::cerr << "Error : " << std::endl;
        return (1);
    }
    OtpClass otp;
    return (0);
}
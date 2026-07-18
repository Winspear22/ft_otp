/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 19:33:55 by adaloui           #+#    #+#             */
/*   Updated: 2026/07/18 18:57:07 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.hpp"
#include "ArgsParser.hpp"
#include "OtpGClass.hpp"

int main(int argc, char **argv)
{
    if (ArgsParser::parseArguments(argc, argv) == FAILURE)
    {
        return (1);
    }
    OtpGClass generate(argv);
    return (0);
}
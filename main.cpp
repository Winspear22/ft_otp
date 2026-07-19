/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 19:33:55 by adaloui           #+#    #+#             */
/*   Updated: 2026/07/19 16:53:05 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.hpp"
#include "ArgsParser.hpp"
#include "OtpGClass.hpp"
#include "OtpKClass.hpp"

int main(int argc, char **argv)
{
    if (ArgsParser::parseArguments(argc, argv) == FAILURE)
        return (1);

    std::string flag = argv[1];

    if (flag == "-g")
    {
        OtpGClass generateG(argv);
        generateG.readKey();
        generateG.encryptKey();
        generateG.writeKeyFile();
    }
    else if (flag == "-k")
    {
        OtpKClass generateK;
        generateK.readKeyFile();
        generateK.decryptKey();
        generateK.generateTotp();
    }
    return (0);
}
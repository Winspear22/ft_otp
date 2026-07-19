/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 19:33:55 by adaloui           #+#    #+#             */
/*   Updated: 2026/07/19 17:08:30 by adaloui          ###   ########.fr       */
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
        if (generateG.readKey() == FAILURE)
            return (1);
        if (generateG.encryptKey() == FAILURE)
            return (1);
        if (generateG.writeKeyFile() == FAILURE)
            return (1);
    }
    else if (flag == "-k")
    {
        OtpKClass generateK;
        if (generateK.readKeyFile() == FAILURE)
            return (1);
        if (generateK.decryptKey() == FAILURE)
            return (1);
        generateK.generateTotp();
    }
    return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ArgsParser.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 20:16:32 by adaloui           #+#    #+#             */
/*   Updated: 2026/07/15 21:10:36 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ArgsParser.hpp"

ArgsParser::ArgsParser(void) {}

ArgsParser::ArgsParser(const ArgsParser &other)
{
    *this = other;
}

ArgsParser &ArgsParser::operator=(const ArgsParser &other)
{
    if (this != &other) {}
    return *this;
}

ArgsParser::~ArgsParser() {}

bool ArgsParser::parseArguments(int argc, char **argv)
{
    int opt;

    while ((opt = getopt(argc, argv, "g:k:")) != -1)
    {
        switch (opt)
        {
            case 'g':
                break; // Ici on utilise la fonction fileContentCheck et fileTypeCheck
            case 'k':
				break; // Ici on utilise la fonction magicNumberCheck
            case '?':
                std::cerr << "Error, you must use either -k <argument> or -g <argument>." << std::endl;
				return (FAILURE);
        }
    }

    return SUCCESS;
}

bool ArgsParser::fileTypeCheck(void)
{
	return SUCCESS;
}

bool ArgsParser::fileContentCheck(void)
{
	return SUCCESS;
}

bool ArgsParser::magicNumberCheck(void)
{
	return SUCCESS;
}

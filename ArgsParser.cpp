/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ArgsParser.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 20:16:32 by adaloui           #+#    #+#             */
/*   Updated: 2026/07/15 20:37:34 by adaloui          ###   ########.fr       */
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

std::string ArgsParser::getFlag(void)
{
	return this->_flag;
}

std::string ArgsParser::getFilePath(void)
{
	return this->_filePath;
}

void		ArgsParser::setFlag(std::string flag)
{
	this->_flag = flag;
}

void		ArgsParser::setFilePath(std::string filePath)
{
	this->_filePath = filePath;
}

bool ArgsParser::parseArguments(int argc, char **argv)
{
    int opt;

    while ((opt = getopt(argc, argv, "g:k:")) != -1)
    {
        switch (opt)
        {
            case 'g':
                break;
            case 'k':
				break;
            case '?':
                std::cerr << "Error, you must use either -k <argument> or -g <argument>." << std::endl;
				return (FAILURE);
        }
    }

    return SUCCESS;
}

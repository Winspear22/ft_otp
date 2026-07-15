/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ArgsParser.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 20:16:32 by adaloui           #+#    #+#             */
/*   Updated: 2026/07/15 21:18:33 by adaloui          ###   ########.fr       */
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
                if (!_fileTypeCheck(optarg) || !_fileContentCheck(optarg))
                    return (FAILURE);
                break;
            case 'k':
                if (!_fileTypeCheck(optarg) || !_magicNumberCheck(optarg))
                    return (FAILURE);
                break;
            case '?':
                std::cerr << "Error, you must use either -k <argument> or -g <argument>." << std::endl;
				return (FAILURE);
        }
    }

    return SUCCESS;
}


bool ArgsParser::_fileTypeCheck(const std::string &filePath)
{
    struct stat fileStat;

    if (stat(filePath.c_str(), &fileStat) != 0)
        return (FAILURE);
    if (!S_ISREG(fileStat.st_mode))
        return (FAILURE);
    if (access(filePath.c_str(), R_OK) != 0)
        return (FAILURE);
    return (SUCCESS);
}

bool ArgsParser::_fileContentCheck(const std::string &filePath)
{
    std::ifstream file(filePath.c_str(), std::ios::binary);
    std::string line;

    if (!file.is_open())
        return (FAILURE);
    if (!std::getline(file, line))
        return (FAILURE);
    file.close();

    // Strip le \r si le fichier vient de Windows
    if (!line.empty() && line.back() == '\r')
        line.pop_back();

    if (line.length() != 64)
        return (FAILURE);
    for (size_t i = 0; i < line.length(); i++)
    {
        if (!std::isxdigit(line[i]))
            return (FAILURE);
    }
    return (SUCCESS);
}

bool ArgsParser::_magicNumberCheck(const std::string &filePath)
{
    std::ifstream file(filePath.c_str(), std::ios::binary);
    char magic[5];

    if (!file.is_open())
        return (FAILURE);
    file.read(magic, 5);
    file.close();

    if (std::strncmp(magic, "FTOTP", 5) != 0)
        return (FAILURE);
    return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ArgsParser.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 20:16:34 by adaloui           #+#    #+#             */
/*   Updated: 2026/07/15 21:14:36 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGSPARSER_HPP
#define ARGSPARSER_HPP

#include "includes.hpp"

class ArgsParser
{
    public:
        ArgsParser(void);
        ArgsParser(const ArgsParser &other);
        ArgsParser &operator=(const ArgsParser &other);
        ~ArgsParser();

        static bool parseArguments(int argc, char **argv);

    private:
        static bool _fileTypeCheck(const std::string &filePath);
        static bool _fileContentCheck(const std::string &filePath);
        static bool _magicNumberCheck(const std::string &filePath);
};


#endif
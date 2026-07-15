/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ArgsParser.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 20:16:34 by adaloui           #+#    #+#             */
/*   Updated: 2026/07/15 20:34:31 by adaloui          ###   ########.fr       */
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

        std::string getFlag();
        std::string getFilePath();

        void        setFlag(std::string flag);
        void        setFilePath(std::string filePath);

    private:
        std::string _flag;
        std::string _filePath;

};


#endif
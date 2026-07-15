/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ArgsParser.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 20:16:34 by adaloui           #+#    #+#             */
/*   Updated: 2026/07/15 21:08:41 by adaloui          ###   ########.fr       */
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
        bool fileTypeCheck(void);
        bool fileContentCheck(void);
        bool magicNumberCheck(void);
};


#endif
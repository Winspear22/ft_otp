/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ArgsParser.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 20:16:34 by adaloui           #+#    #+#             */
/*   Updated: 2026/07/15 20:22:02 by adaloui          ###   ########.fr       */
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

        bool parseArguments(int argc, char **argv);

};


#endif
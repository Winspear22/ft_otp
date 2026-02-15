/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorManager.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adnen <adnen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 15:21:32 by adnen             #+#    #+#             */
/*   Updated: 2026/02/15 15:56:55 by adnen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.hpp"

int ErrorsInMain(std::string mainMessage, std::string errorMessage)
{
	std::cerr << BOLD_WHITE << mainMessage << BOLD_RED << errorMessage << RESET<< std::endl;
	return (1);
}

void ErrorsInClassVoid(std::string mainMessage, std::string errorMessage)
{
	std::cerr << BOLD_WHITE << mainMessage << BOLD_RED << errorMessage << RESET<< std::endl;
	return ;
}
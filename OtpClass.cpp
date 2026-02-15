/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OtpClass.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adnen <adnen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 15:30:42 by adnen             #+#    #+#             */
/*   Updated: 2026/02/15 16:04:40 by adnen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OtpClass.hpp"
#include <cerrno>

OtpClass::OtpClass()
{
	std::cout << BOLD_BLUE << "OtpClass Constructor called." << RESET << std::endl;
}

OtpClass::OtpClass(const OtpClass &src)
{
	std::cout << BOLD_BLUE << "OtpClass copy constuctor called." << RESET << std::endl;
	*this = src;
}

OtpClass &OtpClass::operator=(const OtpClass &src)
{
	std::cout << BOLD_BLUE << "OtpClass operator= called." << RESET << std::endl;
	(void)src;
	return *this;
}

OtpClass::~OtpClass()
{
	std::cout << BOLD_BLUE << "OtpClass Destructor called." << RESET << std::endl;
}

void	OtpClass::readFile(const std::string &fileName)
{
	std::ifstream file(fileName.c_str());
	if (!file.is_open())
		return ErrorsInClassVoid("Error: cannot open file: ", fileName);
	std::string line;

	if (std::getline(file, line))
	{
		std::cout << line << std::endl;
	}
	else
		return ErrorsInClassVoid("Error: ", "file is empty:" + fileName);
	file.close();
}
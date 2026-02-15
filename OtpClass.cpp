/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OtpClass.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adnen <adnen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 15:30:42 by adnen             #+#    #+#             */
/*   Updated: 2026/02/15 16:52:29 by adnen            ###   ########.fr       */
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
		if (this->checkLine(line) == FAILURE)
		{
			file.close();
			return ;
		}
		this->_key = line;
	}
	else
		return ErrorsInClassVoid("Error: ", "file is empty:" + fileName);
	file.close();
}

bool	OtpClass::checkLine(const std::string &line)
{
	int i;

	i = -1;
	if (line.length() != 64)
		return (ErrorsInClassBool("Error: ", "line is not 64 characters long"));
	while (line[++i])
	{
		if (!std::isxdigit(line[i]))
			return (ErrorsInClassBool("Error: ", "line is not hexadecimal"));
	}
	return (SUCCESS);
}

/*
** ATTENTION : la masterKey est fixe et écrite en claire. C'est fait exprès pour 
** simplifier l'exercice car cacher la masterKey n'est pas demandé. Pour un vrai
** projet, la masterKey devrait être stockée dans un fichier sécurisé et 
** accessible uniquement par le processus.
*/
std::string OtpClass::_xorTransform(const std::string &data)
{
	int i;
	std::string masterKey = "coucoulesamisjemappelleadnenetvousvousallezbienmoijevaissuperbi";
	std::string result;
	

	i = -1;
	result = data;
	while (++i < data.size())
		result[i] = data[i] ^ masterKey[i % masterKey.size()];
	return result;
}
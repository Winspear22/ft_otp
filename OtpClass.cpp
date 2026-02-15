/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OtpClass.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adnen <adnen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 15:30:42 by adnen             #+#    #+#             */
/*   Updated: 2026/02/15 17:28:57 by adnen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OtpClass.hpp"
#include "includes.hpp"
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

void OtpClass::setFlag(const std::string &flag)
{ 
	this->_flag = flag; 
}

std::string OtpClass::getFlag() const 
{ 
	return (this->_flag);
}

void OtpClass::readFile(const std::string &fileName)
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
			return;
		}
		this->_key = line;
	}
	else
		return ErrorsInClassVoid("Error: ", "file is empty:" + fileName);
	file.close();
	}

bool OtpClass::checkLine(const std::string &line)
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
	while ((size_t)++i < data.size())
		result[i] = data[i] ^ masterKey[i % masterKey.size()];
	return result;
	}

void OtpClass::saveKey()
{
	std::ofstream file("ft_otp.key", std::ios::out | std::ios::binary);
	if (!file.is_open())
		return ErrorsInClassVoid("Error: cannot open file: ", "ft_otp.key");
	std::string cryptedKey = this->_xorTransform(this->_key);
	file.write(cryptedKey.c_str(), cryptedKey.size());
	file.close();
	std::cout << BOLD_GREEN << "Key saved in ft_otp.key, key : " << BOLD_MAGENTA << cryptedKey << RESET << std::endl;
}
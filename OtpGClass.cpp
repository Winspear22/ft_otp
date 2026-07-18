/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OtpGClass.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 20:48:41 by adaloui           #+#    #+#             */
/*   Updated: 2026/07/15 21:52:34 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OtpGClass.hpp"

OtpGClass::OtpGClass(char **argv) 
{
    this->_flag = argv[1];
    this->_filePath = argv[2];
}

OtpGClass::OtpGClass(const OtpGClass &other)
{
    *this = other;
}

OtpGClass &OtpGClass::operator=(const OtpGClass &other)
{
    if (this != &other)
    {
        this->_flag = other._flag;
        this->_filePath = other._filePath;
    }
    return (*this);
}

OtpGClass::~OtpGClass(void) {}

std::string OtpGClass::getFlag(void)
{
    return (this->_flag);
}

std::string OtpGClass::getFilePath(void)
{
    return (this->_filePath);
}

void		OtpGClass::setFlag(std::string flag)
{
	this->_flag = flag;
}

void		OtpGClass::setFilePath(std::string filePath)
{
	this->_filePath = filePath;
}

void        OtpGClass::setHexKey(std::string hexKey)
{
    this->_hexKey = hexKey;
}

bool        OtpGClass::readKey()
{
    std::filesystem::path path(this->_filePath);
    std::ifstream file(this->_filePath, std::ios::binary);
	if (!file.is_open())
	{
		std::cerr << "Error: Could not open " << this->_filePath << std::endl;
		return FAILURE;
	}

}
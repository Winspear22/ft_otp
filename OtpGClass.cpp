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
        this->_hexKey = other._hexKey;
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

std::string OtpGClass::getHexKey(void)
{
    return (this->_hexKey);
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
    std::ifstream file(this->_filePath, std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open " << this->_filePath << std::endl;
        return FAILURE;
    }
    std::string fileContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    if (fileContent.empty())
    {
        std::cerr << "Error: File is empty" << std::endl;
        return FAILURE;
    }
    if (fileContent.back() == '\n')
        fileContent.pop_back();
    this->setHexKey(fileContent);
    std::cout << "Success: hexKey successfully read." <<std::endl;
    return SUCCESS;
}
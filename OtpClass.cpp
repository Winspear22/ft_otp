/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OtpClass.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 20:48:41 by adaloui           #+#    #+#             */
/*   Updated: 2026/07/15 21:52:34 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OtpClass.hpp"

OtpClass::OtpClass(char **argv) 
{
    this->_flag = argv[1];
    this->_filePath = argv[2];
}

OtpClass::OtpClass(const OtpClass &other)
{
    *this = other;
}

OtpClass &OtpClass::operator=(const OtpClass &other)
{
    if (this != &other)
    {
        this->_flag = other._flag;
        this->_filePath = other._filePath;
    }
    return (*this);
}

OtpClass::~OtpClass(void) {}

std::string OtpClass::getFlag(void)
{
    return (this->_flag);
}

std::string OtpClass::getFilePath(void)
{
    return (this->_filePath);
}

void		OtpClass::setFlag(std::string flag)
{
	this->_flag = flag;
}

void		OtpClass::setFilePath(std::string filePath)
{
	this->_filePath = filePath;
}
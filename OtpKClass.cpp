/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OtpKClass.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 20:55:35 by adaloui           #+#    #+#             */
/*   Updated: 2026/07/18 20:56:44 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OtpKClass.hpp"

OtpKClass::OtpKClass() {}

OtpKClass::OtpKClass(const OtpKClass &other)
{
    *this = other;
}

OtpKClass &OtpKClass::operator=(const OtpKClass &other)
{
    if (this != &other) {}
    return (*this);
}

OtpKClass::~OtpKClass() {}
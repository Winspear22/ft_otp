/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OtpClass.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 20:48:43 by adaloui           #+#    #+#             */
/*   Updated: 2026/07/15 20:51:17 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTPCLASS_HPP
#define OTPCLASS_HPP

#include "includes.hpp"

class OtpClass
{
    public:
		OtpClass(void);
        OtpClass(const OtpClass &other);
        OtpClass &operator=(const OtpClass &other);
        ~OtpClass();
		
		std::string getFlag();
        std::string getFilePath();

        void        setFlag(std::string flag);
        void        setFilePath(std::string filePath);

    private:
        std::string _flag;
        std::string _filePath;
};

#endif
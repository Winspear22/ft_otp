/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OtpClass.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adnen <adnen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 15:30:45 by adnen             #+#    #+#             */
/*   Updated: 2026/03/08 17:34:12 by adnen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __OTPCLASS_HPP__
#define __OTPCLASS_HPP__

#include "includes.hpp"

class OtpClass
{
	public:
		OtpClass();
		OtpClass(const OtpClass &src);
		OtpClass &operator=(const OtpClass &src);
		~OtpClass();

		/*
		** -G flag : generate a key
		*/
		bool		readFile(const std::string &fileName);
		bool		checkLine(const std::string &line);
		void		saveKey();

		/*
		** -K flag : key
		*/
		bool		readEncryptedFile(const std::string &fileName);
		void		generateOTP();	

		void		setFlag(const std::string &flag);
		std::string	getFlag() const;

	private:
		std::string _key;
		std::string						_xorTransform(const std::string &data);
		std::vector<unsigned char>		_hexStringToBytes(const std::string &hex);
		std::string _flag;
};

#endif

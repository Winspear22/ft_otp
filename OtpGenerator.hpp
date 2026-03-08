/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OtpGenerator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adnen <adnen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 18:10:00 by adnen             #+#    #+#             */
/*   Updated: 2026/03/08 18:18:48 by adnen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __OTPGENERATOR_HPP__
#define __OTPGENERATOR_HPP__

#include "includes.hpp"

class OtpGenerator
{
	public:
		OtpGenerator();
		OtpGenerator(const OtpGenerator &src);
		OtpGenerator &operator=(const OtpGenerator &src);
		~OtpGenerator();

		bool readEncryptedFile(const std::string &fileName);
		void generateOTP();

	private:
		std::string _key;
		std::string _xorTransform(const std::string &data);
		std::vector<unsigned char> _hexStringToBytes(const std::string &hex);
		std::vector<unsigned char> _counterToBytes(uint64_t counter);
		std::vector<unsigned char>
		_hmacSHA1(const std::vector<unsigned char> &key,
			const std::vector<unsigned char> &message);
		uint32_t _dynamicCreationOfNumbers(const std::vector<unsigned char> &hmac);
};

#endif

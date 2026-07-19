/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OtpKClass.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 20:54:09 by adaloui           #+#    #+#             */
/*   Updated: 2026/07/19 16:03:28 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTPKCLASS_HPP
#define OTPKCLASS_HPP

#include "includes.hpp"

class OtpKClass
{
    public:
        OtpKClass();
        OtpKClass(const OtpKClass &other);
        OtpKClass &operator=(const OtpKClass &other);
        ~OtpKClass();

		bool	readKeyFile(void);
		bool	decryptKey(void);
		void	generateTotp(void);

    private:
        bool								_readMasterKey(unsigned char *aesKey);
		std::vector<unsigned char>			_iv;
		std::vector<unsigned char>			_ciphertext;
		std::vector<unsigned char>			_decryptedKey;
};

#endif
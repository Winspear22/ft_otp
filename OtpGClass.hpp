/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OtpGClass.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 20:48:43 by adaloui           #+#    #+#             */
/*   Updated: 2026/07/15 21:52:07 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTPGCLASS_HPP
#define OTPGCLASS_HPP

#include "includes.hpp"

class OtpGClass
{
    public:
		OtpGClass(char **argv);
        OtpGClass(const OtpGClass &other);
        OtpGClass &operator=(const OtpGClass &other);
        ~OtpGClass();
		
		std::string getFlag(void);
        std::string getFilePath(void);
        std::string getHexKey(void);

        void        setFlag(std::string flag);
        void        setFilePath(std::string filePath);
        void        setHexKey(std::string hexKey);

        bool        readKey(void);
        bool        encryptKey(void);
		bool		writeKeyFile(void);

    private:
        std::string                 _flag;
        std::string                 _filePath;
        std::string                 _hexKey;
        std::vector<unsigned char>  _iv;
        std::vector<unsigned char>  _ciphertext;

        std::vector<unsigned char>	_hexToBytes(void);
        bool						_generateIv(void);
        bool						_readMasterKey(unsigned char *aesKey);
};

#endif
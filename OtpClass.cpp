/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OtpClass.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adnen <adnen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 15:30:42 by adnen             #+#    #+#             */
/*   Updated: 2026/03/08 17:57:42 by adnen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OtpClass.hpp"
#include "includes.hpp"
#include <cerrno>
#include <cstddef>

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

bool OtpClass::readFile(const std::string &fileName)
{
	std::ifstream file(fileName.c_str());
	if (!file.is_open())
		return ErrorsInClassBool("Error: cannot open file: ", fileName);
	std::string line;

	if (std::getline(file, line))
	{
		if (this->checkLine(line) == FAILURE) 
		{
			file.close();
			return (FAILURE);
		}
		this->_key = line;
	}
	else
		return ErrorsInClassBool("Error: ", "file is empty:" + fileName);
	file.close();
	return (SUCCESS);
}

bool OtpClass::checkLine(const std::string &line)
{
	int i;

	i = -1;
	if (line.length() < 64)
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
	size_t i;
	std::string masterKey = "coucoulesamisjemappelleadnenetvousvousallezbienmoijevaissuperbi";
	std::string result;

	i = 0;
	result = data;
	while (i < data.size())
	{
		result[i] = data[i] ^ masterKey[i % masterKey.size()];
		i++;
	}
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

bool OtpClass::readEncryptedFile(const std::string &fileName)
{
	std::ifstream file(fileName.c_str(), std::ios::binary);
	if (!file.is_open())
		return ErrorsInClassBool("Error: cannot open file: ", fileName);
	
	std::string encryptedData(
		(std::istreambuf_iterator<char>(file)),
		std::istreambuf_iterator<char>()
	);
	file.close();
	this->_key = this->_xorTransform(encryptedData);
	return SUCCESS;
}

std::vector<unsigned char> OtpClass::_hexStringToBytes(const std::string &hex)
{
	size_t i;
	std::vector<unsigned char> bytes;
	std::string byteString;
	unsigned char byte;

	i = 0;
	while (i < hex.length())
	{
		byteString = hex.substr(i, 2);
		byte = static_cast<unsigned char>(std::stoul(byteString, nullptr, 16));
		bytes.push_back(byte);
		i += 2;
	}
	return bytes;
}

std::vector<unsigned char> OtpClass::_counterToBytes(uint64_t counter)
{
	std::vector<unsigned char> bytes(8);
	bytes[0] = (counter >> 56) & 0xFF;  // octet le plus lourd
	bytes[1] = (counter >> 48) & 0xFF;
	bytes[2] = (counter >> 40) & 0xFF;
	bytes[3] = (counter >> 32) & 0xFF;
	bytes[4] = (counter >> 24) & 0xFF;
	bytes[5] = (counter >> 16) & 0xFF;
	bytes[6] = (counter >> 8) & 0xFF;
	bytes[7] = counter & 0xFF;          // octet le plus léger
	return bytes;
}

std::vector<unsigned char> OtpClass::_hmacSHA1(
	const std::vector<unsigned char> &key,
	const std::vector<unsigned char> &message)
{
	// --- ÉTAPE 1 : Préparer la clé ---
	// Si la clé est trop longue (> 64 octets), on la hash d'abord

	std::vector<unsigned char> keyToUse;
	if (key.size() > 64)
	{
		// SHA1 prend : (données, taille, buffer de sortie)
		// Elle retourne toujours 20 octets (SHA_DIGEST_LENGTH = 20)
		unsigned char hashedKey[SHA_DIGEST_LENGTH];
		SHA1(key.data(), key.size(), hashedKey);
		keyToUse.assign(hashedKey, hashedKey + SHA_DIGEST_LENGTH);
	}
	else
		keyToUse = key;

	// --- ÉTAPE 2 : Padding de la clé à 64 octets ---
	// resize(64, 0x00) : si la clé fait 32 octets, on ajoute 32 zéros à la fin
	keyToUse.resize(64, 0x00);

	// --- ÉTAPE 3 : Créer inner_key et outer_key ---

	std::vector<unsigned char> innerKey(64);
	std::vector<unsigned char> outerKey(64);
	size_t i = 0;
	while (i < 64)
	{
		innerKey[i] = keyToUse[i] ^ 0x36;  // chaque octet XOR ipad
		outerKey[i] = keyToUse[i] ^ 0x5C;  // chaque octet XOR opad
		i++;
	}

	// --- ÉTAPE 4 : Hash intérieur ---
	// inner_data = innerKey (64 octets) + message (8 octets)

	std::vector<unsigned char> innerData(innerKey.begin(), innerKey.end());
	innerData.insert(innerData.end(), message.begin(), message.end());

	// On hash inner_data avec SHA1 → donne 20 octets
	unsigned char innerHash[SHA_DIGEST_LENGTH];
	SHA1(innerData.data(), innerData.size(), innerHash);

	// --- ÉTAPE 5 : Hash extérieur ---
	// outer_data = outerKey (64 octets) + innerHash (20 octets)

	std::vector<unsigned char> outerData(outerKey.begin(), outerKey.end());
	outerData.insert(outerData.end(), innerHash, innerHash + SHA_DIGEST_LENGTH);

	// On hash outer_data avec SHA1 → donne 20 octets : LE RÉSULTAT

	unsigned char finalHash[SHA_DIGEST_LENGTH];
	SHA1(outerData.data(), outerData.size(), finalHash);
	// On retourne les 20 octets du résultat
	return std::vector<unsigned char>(finalHash, finalHash + SHA_DIGEST_LENGTH);
}

uint32_t OtpClass::_dynamicCreationOfNumbers(const std::vector<unsigned char> &hmac)
{
	int offset = hmac[19] & 0x0F;

	uint32_t code = ((hmac[offset] & 0x7F) << 24)
				  | ((hmac[offset + 1] & 0xFF) << 16)
				  | ((hmac[offset + 2] & 0xFF) << 8)
				  | (hmac[offset + 3] & 0xFF);
	return code % 1000000;
}

void OtpClass::generateOTP()
{
	// Étape 2 : "b598975d..." → {0xb5, 0x98, 0x97, 0x5d, ...}
	std::vector<unsigned char> keyBytes = this->_hexStringToBytes(this->_key);
	// Étape 3 : Secondes depuis 1970, divisées par 30
	uint64_t timeCounter = static_cast<uint64_t>(std::time(nullptr)) / 30;
	// Étape 4 : Le compteur en 8 octets big-endian
	std::vector<unsigned char> counterBytes = this->_counterToBytes(timeCounter);
	// Étape 5 : HMAC-SHA1
	std::vector<unsigned char> hmac = this->_hmacSHA1(keyBytes, counterBytes);
	// Étape 6 : Extraire 6 chiffres
	uint32_t otp = this->_dynamicCreationOfNumbers(hmac);
	// Étape 7 : Afficher avec padding de zéros (ex: 42 → "000042")
	std::cout << std::setfill('0') << std::setw(6) << otp << std::endl;
}
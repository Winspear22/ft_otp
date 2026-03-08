/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OtpGenerator.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adnen <adnen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 18:10:00 by adnen             #+#    #+#             */
/*   Updated: 2026/03/08 18:22:32 by adnen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OtpGenerator.hpp"

OtpGenerator::OtpGenerator()
{
	std::cout << BOLD_BLUE << "OtpGenerator Constructor called." << RESET << std::endl;
}

OtpGenerator::OtpGenerator(const OtpGenerator &src)
{
	std::cout << BOLD_BLUE << "OtpGenerator copy constructor called." << RESET << std::endl;
	*this = src;
}

OtpGenerator &OtpGenerator::operator=(const OtpGenerator &src)
{
	std::cout << BOLD_BLUE << "OtpGenerator operator= called." << RESET << std::endl;
	(void)src;
	return *this;
}

OtpGenerator::~OtpGenerator()
{
	std::cout << BOLD_BLUE << "OtpGenerator Destructor called." << RESET << std::endl;
}

/*
** ATTENTION : la masterKey est fixe et écrite en claire. C'est fait exprès pour
** simplifier l'exercice car cacher la masterKey n'est pas demandé. Pour un vrai
** projet, la masterKey devrait être stockée dans un fichier sécurisé et
** accessible uniquement par le processus.
*/
std::string OtpGenerator::_xorTransform(const std::string &data)
{
	size_t i;
	std::string masterKey =
		"coucoulesamisjemappelleadnenetvousvousallezbienmoijevaissuperbi";
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

bool OtpGenerator::readEncryptedFile(const std::string &fileName)
{
	std::ifstream file(fileName.c_str(), std::ios::binary);
	if (!file.is_open())
		return ErrorsInClassBool("Error: cannot open file: ", fileName);

	std::string encryptedData((std::istreambuf_iterator<char>(file)),
											std::istreambuf_iterator<char>());
	file.close();
	this->_key = this->_xorTransform(encryptedData);
	return SUCCESS;
}

std::vector<unsigned char>
OtpGenerator::_hexStringToBytes(const std::string &hex)
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

std::vector<unsigned char> OtpGenerator::_counterToBytes(uint64_t counter)
{
	std::vector<unsigned char> bytes(8);
	bytes[0] = (counter >> 56) & 0xFF; // octet le plus lourd
	bytes[1] = (counter >> 48) & 0xFF;
	bytes[2] = (counter >> 40) & 0xFF;
	bytes[3] = (counter >> 32) & 0xFF;
	bytes[4] = (counter >> 24) & 0xFF;
	bytes[5] = (counter >> 16) & 0xFF;
	bytes[6] = (counter >> 8) & 0xFF;
	bytes[7] = counter & 0xFF; // octet le plus léger
	return bytes;
}

std::vector<unsigned char>
OtpGenerator::_hmacSHA1(const std::vector<unsigned char> &key,
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
		innerKey[i] = keyToUse[i] ^ 0x36; // chaque octet XOR ipad
		outerKey[i] = keyToUse[i] ^ 0x5C; // chaque octet XOR opad
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

uint32_t OtpGenerator::_dynamicCreationOfNumbers(const std::vector<unsigned char> &hmac)
{
	int offset; 
	uint32_t code;
	
	offset = hmac[19] & 0x0F;
	code = ((hmac[offset] & 0x7F) << 24) |
    ((hmac[offset + 1] & 0xFF) << 16) |
	((hmac[offset + 2] & 0xFF) << 8) | 
	(hmac[offset + 3] & 0xFF);

	return code % 1000000;
}

void OtpGenerator::generateOTP()
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

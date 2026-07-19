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
        this->_iv = other._iv;
        this->_ciphertext = other._ciphertext;
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
    //std::cout << "Success: hexKey successfully read." <<std::endl;
    return SUCCESS;
}

std::vector<unsigned char>    OtpGClass::_hexToBytes(void)
{
    std::vector<unsigned char>  keyBytes;
    auto i = -1;

    // On parcourt la string hex 2 chars par 2
    // "31323334" → [0x31, 0x32, 0x33, 0x34]
    while (++i + 1 < static_cast<int>(this->_hexKey.length()))
    {
        std::string byteStr = this->_hexKey.substr(i, 2);
        // On convertit la paire hex en un byte (0-255)
        unsigned char byte = static_cast<unsigned char>(std::stoi(byteStr, nullptr, 16));
        keyBytes.push_back(byte);
        i += 1;
    }
    return (keyBytes);
}

bool    OtpGClass::_generateIv(void)
{
    unsigned char iv[16];

    // RAND_bytes génère des bytes cryptographiquement aléatoires
    // L'IV n'est pas secret, mais il doit être unique pour chaque chiffrement
    if (RAND_bytes(iv, 16) != 1)
    {
        std::cerr << "Error: Failed to generate IV" << std::endl;
        return (FAILURE);
    }
    // On stocke l'IV pour l'écrire dans ft_otp.key plus tard
    this->_iv.assign(iv, iv + 16);
    return (SUCCESS);
}

bool    OtpGClass::encryptKey(void)
{
    // 1. Convertir la clé hex en bytes
    std::vector<unsigned char> keyBytes = this->_hexToBytes();

    // 2. Préparer la clé AES-256 (32 bytes)
    unsigned char aesKey[32];
    if (this->_readMasterKey(aesKey) == FAILURE)
        return (FAILURE);

    // 3. Générer un IV aléatoire (16 bytes)
    if (this->_generateIv() == FAILURE)
        return (FAILURE);

    // 4. Créer le contexte de chiffrement OpenSSL
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx)
        return (FAILURE);

    // 5. Initialiser : on dit à OpenSSL "chiffre en AES-256-CBC avec cette clé et cet IV"
    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, aesKey, this->_iv.data()) != 1)
        return (EVP_CIPHER_CTX_free(ctx), FAILURE);

    // 6. Préparer le buffer de sortie (plaintext + 1 bloc de 16 pour le padding)
    int ciphertextLen = 0;
    int finalLen = 0;
    this->_ciphertext.resize(keyBytes.size() + 16);

    // 7. Chiffrer le plaintext → ciphertext
    if (EVP_EncryptUpdate(ctx, this->_ciphertext.data(), &ciphertextLen, keyBytes.data(), keyBytes.size()) != 1)
        return (EVP_CIPHER_CTX_free(ctx), FAILURE);

    // 8. Finaliser : ajoute le padding PKCS7 et termine le chiffrement
    if (EVP_EncryptFinal_ex(ctx, this->_ciphertext.data() + ciphertextLen, &finalLen) != 1)
        return (EVP_CIPHER_CTX_free(ctx), FAILURE);

    // 9. Ajuster la taille du ciphertext à la vraie taille
    this->_ciphertext.resize(ciphertextLen + finalLen);

    // 10. Libérer le contexte
    EVP_CIPHER_CTX_free(ctx);
    return (SUCCESS);
}

bool    OtpGClass::writeKeyFile(void)
{
    std::ofstream file("ft_otp.key", std::ios::out | std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not create ft_otp.key" << std::endl;
        return (FAILURE);
    }

    // 1. Écrire le magic number (5 bytes)
    const char *magic = "FTOTP";
    file.write(magic, 5);

    // 2. Écrire l'IV (16 bytes on utilise reinterpret cast car les vector ont des unsigned char)
    file.write(reinterpret_cast<const char *>(this->_iv.data()), this->_iv.size());

    // 3. Écrire le ciphertext
    file.write(reinterpret_cast<const char *>(this->_ciphertext.data()), this->_ciphertext.size());

    file.close();
    return (SUCCESS);
}

bool    OtpGClass::_readMasterKey(unsigned char *aesKey)
{
	std::ifstream file(".ft_otp_master", std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open .ft_otp_master" << std::endl;
        return (FAILURE);
    }
    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    if (content.size() < 32)
    {
        std::cerr << "Error: Master key too short" << std::endl;
        return (FAILURE);
    }
    std::memcpy(aesKey, content.c_str(), 32);
    file.close();
    return (SUCCESS);
}
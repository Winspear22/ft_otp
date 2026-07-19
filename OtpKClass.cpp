/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OtpKClass.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 20:55:35 by adaloui           #+#    #+#             */
/*   Updated: 2026/07/19 15:59:10 by adaloui          ###   ########.fr       */
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
    if (this != &other)
    {
        (void)other;
    }
    return (*this);
}

OtpKClass::~OtpKClass() {}

bool    OtpKClass::_readMasterKey(unsigned char *aesKey)
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

bool    OtpKClass::readKeyFile(void)
{
    std::ifstream file("ft_otp.key", std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open ft_otp.key" << std::endl;
        return (FAILURE);
    }

    // 1. Lire et vérifier le magic number "FTOTP" (5 bytes)
    char magic[5];
    file.read(magic, 5);
    if (std::memcmp(magic, "FTOTP", 5) != 0)
    {
        std::cerr << "Error: Invalid key file" << std::endl;
        return (FAILURE);
    }

    // 2. Lire l'IV (16 bytes)
    this->_iv.resize(16);
    file.read(reinterpret_cast<char *>(this->_iv.data()), 16);

    // 3. Lire tout le reste → ciphertext
    this->_ciphertext.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    file.close();
    return (SUCCESS);
}

bool    OtpKClass::decryptKey(void)
{
    // 1. Récupérer la clé master
    unsigned char aesKey[32];
    if (this->_readMasterKey(aesKey) == FAILURE)
        return (FAILURE);

    // 2. Créer le contexte de déchiffrement
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx)
        return (FAILURE);

    // 3. Initialiser le déchiffrement
    if (EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, aesKey, this->_iv.data()) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        return (FAILURE);
    }

    // 4. Préparer le buffer de sortie
    int decryptedLen = 0;
    int finalLen = 0;
    this->_decryptedKey.resize(this->_ciphertext.size());

    // 5. Déchiffrer
    if (EVP_DecryptUpdate(ctx, this->_decryptedKey.data(), &decryptedLen, this->_ciphertext.data(), this->_ciphertext.size()) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        return (FAILURE);
    }

    // 6. Finaliser (retire le padding PKCS7)
    if (EVP_DecryptFinal_ex(ctx, this->_decryptedKey.data() + decryptedLen, &finalLen) != 1)
    {
        std::cerr << "Error: Decryption failed" << std::endl;
        EVP_CIPHER_CTX_free(ctx);
        return (FAILURE);
    }

    // 7. Ajuster la taille
    this->_decryptedKey.resize(decryptedLen + finalLen);
    EVP_CIPHER_CTX_free(ctx);
    return (SUCCESS);
}
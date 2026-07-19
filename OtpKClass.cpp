/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OtpKClass.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 20:55:35 by adaloui           #+#    #+#             */
/*   Updated: 2026/07/19 16:43:06 by adaloui          ###   ########.fr       */
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

void    OtpKClass::generateTotp(void)
{
    // === RFC 6238 : calculer T ===
    // time(nullptr) = timestamp actuel en secondes
    // On divise par 30 → le compteur change toutes les 30 secondes
    unsigned long long T = static_cast<unsigned long long>(time(nullptr)) / 30;

    // === Convertir T en 8 bytes big-endian ===
    // T est un nombre (ex: 48392017)
    // HMAC-SHA1 attend les données en bytes, pas en nombre
    // Big-endian = le byte le plus significatif en premier
    unsigned char timeBytes[8];
    for (int i = 7; i >= 0; i--)
    {
        timeBytes[i] = T & 0xFF;  // On prend le byte le plus faible
        T >>= 8;                  // On décale de 8 bits vers la droite
    }

    // === RFC 4226 : HMAC-SHA1 ===
    // HMAC(Key, Message) = un hash de 20 bytes (SHA1 = 160 bits = 20 bytes)
    unsigned char hmacResult[20];
    unsigned int hmacLen = 20;
    HMAC(EVP_sha1(), this->_decryptedKey.data(), this->_decryptedKey.size(), timeBytes, 8, hmacResult, &hmacLen);

    // === RFC 4226 : Dynamic Truncation ===
    // Le dernier byte du HMAC détermine l'offset
    // On prend 4 bytes à partir de cet offset
    int offset = hmacResult[19] & 0x0F;  // 0x0F = 00001111 → garde que les 4 derniers bits

    // On extrait 4 bytes à partir de l'offset et on les combine en un int
    // Le & 0x7F sur le premier byte force le bit de signe à 0 → toujours positif
    int binary =
        ((hmacResult[offset] & 0x7F) << 24) |
        ((hmacResult[offset + 1] & 0xFF) << 16) |
        ((hmacResult[offset + 2] & 0xFF) << 8) |
        (hmacResult[offset + 3] & 0xFF);

    // === RFC 4226 : modulo 10^6 → 6 digits ===
    int otp = binary % 1000000;

    // Afficher avec des zéros devant si nécessaire (ex: 004521)
    std::cout << std::setfill('0') << std::setw(6) << otp << std::endl;
}
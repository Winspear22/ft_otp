/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KeyGenerator.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adnen <adnen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 18:10:00 by adnen             #+#    #+#             */
/*   Updated: 2026/03/08 18:17:58 by adnen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "KeyGenerator.hpp"

KeyGenerator::KeyGenerator()
{
  std::cout << BOLD_BLUE << "KeyGenerator Constructor called." << RESET
            << std::endl;
}

KeyGenerator::KeyGenerator(const KeyGenerator &src) {
  std::cout << BOLD_BLUE << "KeyGenerator copy constructor called." << RESET
            << std::endl;
  *this = src;
}

KeyGenerator &KeyGenerator::operator=(const KeyGenerator &src) {
  std::cout << BOLD_BLUE << "KeyGenerator operator= called." << RESET
            << std::endl;
  (void)src;
  return *this;
}

KeyGenerator::~KeyGenerator() {
  std::cout << BOLD_BLUE << "KeyGenerator Destructor called." << RESET
            << std::endl;
}

bool KeyGenerator::readFile(const std::string &fileName) {
  std::ifstream file(fileName.c_str());
  if (!file.is_open())
    return ErrorsInClassBool("Error: cannot open file: ", fileName);
  std::string line;

  if (std::getline(file, line)) {
    if (this->_checkLine(line) == FAILURE) {
      file.close();
      return (FAILURE);
    }
    this->_key = line;
  } else
    return ErrorsInClassBool("Error: ", "file is empty:" + fileName);
  file.close();
  return (SUCCESS);
}

bool KeyGenerator::_checkLine(const std::string &line) {
  int i;

  i = -1;
  if (line.length() < 64)
    return (ErrorsInClassBool("Error: ", "line is not 64 characters long"));
  while (line[++i]) {
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
std::string KeyGenerator::_xorTransform(const std::string &data) {
  size_t i;
  std::string masterKey =
      "coucoulesamisjemappelleadnenetvousvousallezbienmoijevaissuperbi";
  std::string result;

  i = 0;
  result = data;
  while (i < data.size()) {
    result[i] = data[i] ^ masterKey[i % masterKey.size()];
    i++;
  }
  return result;
}

void KeyGenerator::saveKey() {
  std::ofstream file("ft_otp.key", std::ios::out | std::ios::binary);
  if (!file.is_open())
    return ErrorsInClassVoid("Error: cannot open file: ", "ft_otp.key");
  std::string cryptedKey = this->_xorTransform(this->_key);
  file.write(cryptedKey.c_str(), cryptedKey.size());
  file.close();
  std::cout << BOLD_GREEN << "Key saved in ft_otp.key, key : " << BOLD_MAGENTA
            << cryptedKey << RESET << std::endl;
}

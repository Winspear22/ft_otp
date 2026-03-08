/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adnen <adnen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 14:03:04 by adnen             #+#    #+#             */
/*   Updated: 2026/03/08 18:18:13 by adnen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "KeyGenerator.hpp"
#include "OtpGenerator.hpp"
#include "includes.hpp"
#include <cstdlib>

int main(int argc, char **argv)
{
  if (argc != 3)
    return (
        ErrorsInMain("Error wrong number of arguments: ",
                     "Usage: " + std::string(argv[0]) + " <-k | -g> <secret>"));
  std::string flag;
  flag = argv[1];

  if (flag != "-k" && flag != "-g")
    return (
        ErrorsInMain("Error wrong argument: ",
                     "Usage: " + std::string(argv[0]) + " <-k | -g> <secret>"));

  if (flag == "-g") {
    KeyGenerator gen;
    if (gen.readFile(argv[2]) == FAILURE)
      return (EXIT_FAILURE);
    gen.saveKey();
  } else if (flag == "-k") {
    OtpGenerator otp;
    if (otp.readEncryptedFile(argv[2]) == FAILURE)
      return (EXIT_FAILURE);
    otp.generateOTP();
  }
  return (EXIT_SUCCESS);
}

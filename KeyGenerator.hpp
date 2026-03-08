/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KeyGenerator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adnen <adnen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 18:10:00 by adnen             #+#    #+#             */
/*   Updated: 2026/03/08 18:23:17 by adnen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __KEYGENERATOR_HPP__
#define __KEYGENERATOR_HPP__

#include "includes.hpp"

class KeyGenerator
{
	public:
  		KeyGenerator();
  		KeyGenerator(const KeyGenerator &src);
  		KeyGenerator &operator=(const KeyGenerator &src);
  		~KeyGenerator();

  		bool readFile(const std::string &fileName);
  		void saveKey();

	private:
  		std::string _key;
  		bool _checkLine(const std::string &line);
  		std::string _xorTransform(const std::string &data);
};

#endif

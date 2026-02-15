/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OtpClass.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adnen <adnen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 15:30:45 by adnen             #+#    #+#             */
/*   Updated: 2026/02/15 17:20:48 by adnen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __OTPCLASS_HPP__
#define __OTPCLASS_HPP__

#include "includes.hpp"

class OtpClass
{
	public:
		OtpClass();
		OtpClass(const OtpClass &src);
		OtpClass &operator=(const OtpClass &src);
		~OtpClass();

		void		readFile(const std::string &fileName);
		bool		checkLine(const std::string &line);

		void		setFlag(const std::string &flag);
		std::string	getFlag() const;

		void		saveKey();

	private:
		std::string _key;
		std::string _xorTransform(const std::string &data);
		std::string _flag;
};

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OtpClass.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adnen <adnen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 15:30:45 by adnen             #+#    #+#             */
/*   Updated: 2026/02/15 15:54:35 by adnen            ###   ########.fr       */
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
	private:
	
};

#endif

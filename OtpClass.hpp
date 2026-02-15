/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OtpClass.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adnen <adnen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 15:30:45 by adnen             #+#    #+#             */
/*   Updated: 2026/02/15 15:46:04 by adnen            ###   ########.fr       */
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
	private:
	
};

#endif

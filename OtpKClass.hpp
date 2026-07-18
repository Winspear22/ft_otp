/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OtpKClass.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 20:54:09 by adaloui           #+#    #+#             */
/*   Updated: 2026/07/18 20:56:39 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTPKCLASS_HPP
#define OTPKCLASS_HPP

class OtpKClass
{
    public:
        OtpKClass();
        OtpKClass(const OtpKClass &other);
        OtpKClass &operator=(const OtpKClass &other);
        ~OtpKClass();
    private:
};

#endif
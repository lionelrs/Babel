/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** ValidateIp
*/

#ifndef VALIDATEIP_HPP_
#define VALIDATEIP_HPP_

#include <arpa/inet.h>
#include <string>

namespace Babel {
    class ValidateIp {
        public:
            ValidateIp();
            ~ValidateIp();

            bool validateIpAddress(const std::string &ipAddress);
        protected:
        private:
    };
}

#endif /* !VALIDATEIP_HPP_ */

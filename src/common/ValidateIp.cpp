/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** ValidateIp
*/

#include "ValidateIp.hpp"

Babel::ValidateIp::ValidateIp()
{
}

Babel::ValidateIp::~ValidateIp()
{
}

bool Babel::ValidateIp::validateIpAddress(const std::string &ipAddress)
{
    struct sockaddr_in sa;
    int result = inet_pton(AF_INET, ipAddress.c_str(), &(sa.sin_addr));
    return result != 0;
}
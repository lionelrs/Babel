/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** SEPCommands
*/

#ifndef SEPCOMMANDS_HPP_
#define SEPCOMMANDS_HPP_

#include "ISEPCommand.hpp"
#include <iostream>

struct SEPCommands
{
    short port;
    int code;
    char ip[1024];
};


#endif /* !SEPCOMMANDS_HPP_ */
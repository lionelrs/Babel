/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** SEPCommands
*/

#ifndef SEPCOMMANDS_HPP_
#define SEPCOMMANDS_HPP_

#include <iostream>

struct SEPCommands
{
    short port;
    int code;
    char ip[1024];
};

enum SEPCode {
    PING = 100,
    CONNECTION_OK = 200,
    REQUEST_CO = 300,
    REQUEST_CALL = 400,
    CO_ERROR = 500,
    ERROR = 550,
    REQUEST_USERS = 600,
    DISCONECT = 700
};

#endif /* !SEPCOMMANDS_HPP_ */
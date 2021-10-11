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

enum SEPCode
{
    PING = 100,
    PING_IP  = 120,
    USER_CO = 150,
    CONNECTION_OK = 200,
    USER_DECO = 250,
    REQUEST_CO = 300,
    REQUEST_CALL = 400,
    USERCALLBACKRESPONSE = 420,
    USERCALLBACKCONFIRMATION = 430,
    CALL_CONFIRMATION = 435,
    CALL = 450,
    CALLREFUSED = 460,
    CALLHANGUP = 470,
    ALREADYINCALL = 480,
    CO_ERROR = 500,
    ERROR = 550,
    NOT_LOGGED = 580,
    REQUEST_USERS = 600,
    USER_LIST = 650,
    DISCONECT = 700
};

#endif /* !SEPCOMMANDS_HPP_ */
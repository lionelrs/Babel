/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** ASEPCommand
*/

#ifndef ISEPCOMMAND_HPP_
#define ISEPCOMMAND_HPP_

#include <iostream>
#include <vector>

class ASEPCommand {
public:
    virtual ~ASEPCommand() = 0;

    int     getCode() {
        return _code;
    };

    virtual std::string     runFonction(std::vector<std::string> arg) = 0;

protected:
    int     _code;
private:
};

#endif /* !ISEPCOMMAND_HPP_ */
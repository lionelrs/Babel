/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** ISEPCommand
*/

#ifndef ISEPCOMMAND_HPP_
#define ISEPCOMMAND_HPP_

#include <iostream>

class ISEPCommand {
public:
    virtual ~ISEPCommand() = 0;

    virtual int             getCode() = 0;

    virtual std::string     resultCommand() = 0;

protected:
private:
};

#endif /* !ISEPCOMMAND_HPP_ */
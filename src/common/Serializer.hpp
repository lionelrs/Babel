/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** Serializer
*/

#ifndef SERIALIZER_HPP_
#define SERIALIZER_HPP_

#include "SEPCommands.hpp"
#include <ctime>
#include <iostream>
#include <string>
#include <cstdint>
#include <cstring>

#include "asio.hpp"


class Serializer {
public:
    static std::string serialize(SEPCommands command)
    {
        char buff[sizeof(command) + 1];
        std::memset(buff, '\0', sizeof(command) + 1);

        std::memcpy(buff, &command, sizeof(command));

        return (std::string(buff));
    }
    static SEPCommands      *unSerialize(const char * buff)
    {
        SEPCommands *test = (SEPCommands *)buff;
        return (test);
    }

protected:
private:
};

#endif /* !SERIALIZER_HPP_ */
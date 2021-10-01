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


class Serializer {
public:
    static char*            serialize(const SEPCommands &command)
    {
        char *buff = new char(sizeof(command));
        std::memcpy(buff, &command, sizeof(buff));
        return buff;
    }
    static SEPCommands      *unSerialize(char * buff)
    {
        void *command = NULL;
        command = buff;
        SEPCommands *test = static_cast<SEPCommands *>(command);
        std::cout << "In unSerialize function: " << test->code << std::endl;
        return (test);
    }

protected:
private:
};

#endif /* !SERIALIZER_HPP_ */
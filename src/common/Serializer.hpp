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
    static asio::mutable_buffers_1 serialize(const SEPCommands &command)
    {
        char buff[sizeof(command)];

        std::memcpy(buff, &command, sizeof(buff));

        std::cout << buff << std::endl;

        return asio::buffer(buff);
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
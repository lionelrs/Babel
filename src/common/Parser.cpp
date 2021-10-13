/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** Parser
*/

#include "Parser.hpp"

Parser::Parser(int arraySize) : _arraySize(arraySize)
{
}

Parser::~Parser()
{
}

float *Parser::rebuildSoundFromString(std::string s)
{
    float *new_arr = new float[_arraySize]();
    size_t pos = 0;
    std::string token;
    std::string delimiter = ";";
    for (int i = 0; (pos = s.find(delimiter)) != std::string::npos; i++){
        token = s.substr(0, pos);
        new_arr[i] = std::stof(token);
        s.erase(0, pos + delimiter.length());
    }
    return (new_arr);
}

std::string Parser::buildSoundFromSoundBuffer(float *array)
{
    std::stringstream ss;

    for (int i = 0; i < _arraySize; i++) {
        ss << array[i];
        ss << ";";
    }

    return (ss.str());
}

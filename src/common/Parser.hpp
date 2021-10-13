/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** Parser
*/

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <iostream>
#include <string>
#include <sstream>

class Parser {
    public:
        Parser(int arraySize);
        ~Parser();

        float *rebuildSoundFromString(std::string s);
        std::string buildSoundFromSoundBuffer(float *array);



    protected:
    private:

        int _arraySize;
};

#endif /* !PARSER_HPP_ */

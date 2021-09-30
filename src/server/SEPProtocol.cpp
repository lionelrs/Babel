/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** SEPProtocol
*/

#include "SEPProtocol.hpp"

SEPProtocol::SEPProtocol()
{

}

SEPProtocol::~SEPProtocol()
{
}

std::string SEPProtocol::processCommand(const std::string &cliInput)
{
    return "";
}

std::vector<std::string> SEPProtocol::getInfosCommand(std::string command) const
{
    std::vector<std::string> arr;
    std::size_t pos = 0;
    std::string word;
    int lenght = 0;

    while ((pos = command.find(";")) != std::string::npos) {
        word = command.substr(0, pos);
        if (word != "")
            arr.push_back(word);
        for (int i = pos; command[i] == ';'; i++)
            lenght++;
        command.erase(0, pos + lenght);
        lenght = 0;
    }
    if (command != "")
        arr.push_back(command);

    return arr;
}

ISEPCommand* SEPProtocol::whosThatComand(int code) const
{
    return NULL;
}
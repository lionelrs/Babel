/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** SEPProtocol
*/

#include "SEPProtocol.hpp"

SEPProtocol::SEPProtocol()
{
    _allCommands.emplace(300, &SEPProtocol::RequestConnection);
}

SEPProtocol::~SEPProtocol()
{
}

std::string SEPProtocol::processCommand(const std::string &cliInput)
{
    std::cout << "INPUT= " << cliInput << std::endl;
    std::vector<std::string> args = getInfosCommand(cliInput);

    SEPProtocol::factoryF func = _allCommands[std::atoi(args[0].c_str())];

    std::string response = (this->*func)(args);

    return response;
}

std::vector<std::string> SEPProtocol::getInfosCommand(std::string command) const
{
    std::vector<std::string> arr;
    std::size_t pos = 0;
    std::string word;
    int lenght = 0;

    while ((pos = command.find(" ")) != std::string::npos) {
        word = command.substr(0, pos);
        if (word != "")
            arr.push_back(word);
        for (int i = pos; command[i] == ' '; i++)
            lenght++;
        command.erase(0, pos + lenght);
        lenght = 0;
    }
    if (command != "")
        arr.push_back(command);

    // erase \r\n of last args
    arr[arr.size() - 1].erase(arr[arr.size() - 1].size() - 1, 2);

    return arr;
}

std::string SEPProtocol::RequestConnection(const std::vector<std::string> &args)
{
    std::string response = "";

    if (SqliteDataBase::getInstance().checkUserValideLogin(args[1], args[2])) {
            response = "200";
        } else {
            response = "500";
        }
    return response;
}

std::string SEPProtocol::RequestDisconnection(const std::vector<std::string> &args)
{
    std::string response = "";

    SqliteDataBase::getInstance().setUserDisonnected(args[1]);

    return response;
}
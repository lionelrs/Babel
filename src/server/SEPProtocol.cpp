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
    _allCommands.emplace(600, &SEPProtocol::requestUserList);
    _allCommands.emplace(400, &SEPProtocol::requestCall);
    _allCommands.emplace(420, &SEPProtocol::requestCallConfirm);
    _allCommands.emplace(460, &SEPProtocol::requestRefuseCall);
    _allCommands.emplace(470, &SEPProtocol::requestCallHangUp);
    _allCommands.emplace(480, &SEPProtocol::requestAlreadyInCall);
}

SEPProtocol::~SEPProtocol()
{
}

std::string SEPProtocol::requestRefuseCall(const std::vector<std::string> &args)
{

}

std::string SEPProtocol::requestCallHangUp(const std::vector<std::string> &args)
{

}

std::string SEPProtocol::requestAlreadyInCall(const std::vector<std::string> &args)
{
    if (args.size() < 2) return ("500");
    return ("650");
}


std::string SEPProtocol::processCommand(const std::string &cliInput)
{
    std::cout << "INPUT= " << cliInput << std::endl;
    std::vector<std::string> args = getInfosCommand(cliInput);
    SEPProtocol::factoryF func = _allCommands[std::atoi(args[0].c_str())];

    std::string response = (this->*func)(args);

    return response;
}

std::string SEPProtocol::requestCall(const std::vector<std::string> &args)
{
    (void)args;
    std::stringstream ss;
    for (auto itr : args) {
        ss << itr;
        ss << " ";
    }
    return ("450 " + ss.str());
}

std::string SEPProtocol::requestCallConfirm(const std::vector<std::string> &args)
{
    (void)args;
    std::stringstream ss;
    for (auto itr : args) {
        ss << itr;
        ss << " ";
    }
    return ("430 " + ss.str());
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

std::string SEPProtocol::requestUserList(const std::vector<std::string> &args)
{
    (void)args;
    return ("650");
}

std::string SEPProtocol::RequestConnection(const std::vector<std::string> &args)
{
    std::string response = "";
    if (args.size() < 3) return ("500");
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
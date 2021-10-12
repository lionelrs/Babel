/*
** EPITECH PROJECT, 2021
** babel
** File description:
** protocol serveur
*/

#ifndef SEPProtocole
#define SEPProtocole

#include <map>
#include <vector>

#include "../common/SEPCommands.hpp"
#include "../common/Serializer.hpp"

class SEPProtocol {
public:
    SEPProtocol();
    ~SEPProtocol();

    std::string     processCommand(const std::string &cliInput);

protected:
private:
    typedef ISEPCommand* (SEPProtocol::*factoryF)();

    std::vector<std::string>    getInfosCommand(std::string command) const;
    ISEPCommand*                whosThatComand(int code) const;

    std::map<int, factoryF>     _allCommands;
};

#endif /* !SEPProtocole */
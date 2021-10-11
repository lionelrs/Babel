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
#include "SqliteDataBase.hpp"

class SEPProtocol {
public:
    SEPProtocol();
    ~SEPProtocol();

    std::string     processCommand(const std::string &cliInput);
    std::vector<std::string>    getInfosCommand(std::string command) const;

protected:
private:
    typedef std::string (SEPProtocol::*factoryF)(const std::vector<std::string> &arg);


    std::map<int, factoryF>     _allCommands;

    std::string     RequestConnection(const std::vector<std::string> &args);
    std::string     RequestDisconnection(const std::vector<std::string> &args);
    std::string requestUserList(const std::vector<std::string> &args);
    std::string requestCall(const std::vector<std::string> &args);
    std::string requestCallConfirm(const std::vector<std::string> &args);
    std::string requestRefuseCall(const std::vector<std::string> &args);
    std::string requestCallHangUp(const std::vector<std::string> &args);
    std::string requestAlreadyInCall(const std::vector<std::string> &args);
    SqliteDataBase *_instance;
};

#endif /* !SEPProtocole */
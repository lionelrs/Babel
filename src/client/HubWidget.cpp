/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** HubWidget
*/

#include "HubWidget.hpp"

HubWidget::HubWidget(QWidget *parent)
{
    _userList = new QListWidget(parent);

    QLabel *title = new QLabel("Connected user(s)");
    _callButton = new QPushButton("Call");

    QVBoxLayout *outterLayout = new QVBoxLayout(this);
    outterLayout->addWidget(title);
    outterLayout->addWidget(_userList);
    outterLayout->addWidget(_callButton);

    QFont font;
    font.setPointSize(14);
    title->setFont(font);
    _userList->setFont(font);
    _callButton->setFont(font);

    connect(_userList, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(onListItemClicked(QListWidgetItem *)));
    _selected = -1;
}

HubWidget::~HubWidget()
{
}

void HubWidget::onListItemClicked(QListWidgetItem* item)
{
    _selected = _userList->row(item);
}

void HubWidget::addUser(std::string username, std::string ip, int port)
{
    _userList->addItem(username.c_str());
    _userData.push_back(std::make_pair(ip, port));
}

#include <iostream>

void HubWidget::removeUser(std::string username)
{
    int i = 0;
    for (; i < _userList->count(); i++) {
        if (_userList->item(i)->text() == QString::fromStdString(username)) {
            delete _userList->takeItem(i);
            break;
        }
    }
    _userData.erase(_userData.begin() + i);
    for (auto it : _userData) {
        std::cout << it.second << std::endl;
    }
}

QPushButton *HubWidget::getButton() const
{
    return _callButton;
}

int HubWidget::getSelected() const
{
    return _selected;
}

std::string HubWidget::getSelectedName() const
{
    if (_selected == -1)
        return "null";
    return _userList->item(_selected)->text().toStdString();
}

std::string HubWidget::getSelectedIp() const
{
    if (_selected == -1)
        return "null";
    return _userData.at(_selected).first;
}

int HubWidget::getSelectedPort() const
{
    if (_selected == -1)
        return -1;
    return _userData.at(_selected).second;
}
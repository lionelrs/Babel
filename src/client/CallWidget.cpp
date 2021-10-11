/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** CallWidget
*/

#include "CallWidget.hpp"

CallWidget::CallWidget(const std::string callerUsername, const std::string myUsername, QWidget *parent) : _callerUsername(callerUsername), _username(myUsername)
{
    QVBoxLayout *outterLayout = new QVBoxLayout(this);

    _hangUp = new QPushButton("Hang up");
    QLabel myName(myUsername.c_str());
    QLabel callText(("In call with " + callerUsername).c_str());
    outterLayout->addWidget(&callText);
    outterLayout->addWidget(&myName);
    outterLayout->addWidget(_hangUp);

    QFont font;
    font.setPointSize(14);
    _hangUp->setFont(font);
    myName.setFont(font);
    callText.setFont(font);
}

CallWidget::~CallWidget()
{
}

QPushButton *CallWidget::getButton() const
{
    return _hangUp;
}
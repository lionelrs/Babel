/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** Window
*/

#include "Window.hpp"
#include <iostream>

Window::Window()
{
    editor = new QTextEdit();
    _button = new QPushButton(tr("&Send message"));


    // connect(_udp->getSocket(), SIGNAL(messageSent()), this, SLOT(setMessage()));

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(_button);
    buttonLayout->addStretch();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(editor);
    layout->addLayout(buttonLayout);

    setWindowTitle(tr("Custom Type Sending"));
}

Window::~Window()
{
}

void Window::sendMessage()
{
    _message = Message(editor->toPlainText(), _message.headers());
    emit messageSent(_message);
}

Message Window::setAndGetThisMessage()
{
    _message = Message(editor->toPlainText(), _message.headers());
    return (this->_message);
}

void Window::setMessage(const Message &message)
{
    _message = message;
    editor->setPlainText(_message.body());
}

QPushButton *Window::getButton() const
{
    return (this->_button);
}
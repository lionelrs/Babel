/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** Window
*/

#include "Window.hpp"

Window::Window()
{
    editor = new QTextEdit();
    QPushButton *sendButton = new QPushButton(tr("&Send message"));

    connect(sendButton, SIGNAL(clicked()), this, SLOT(sendMessage()));

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(sendButton);
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
    thisMessage = Message(editor->toPlainText(), thisMessage.headers());
    emit messageSent(thisMessage);
}

void Window::setMessage(const Message &message)
{
    thisMessage = message;
    editor->setPlainText(thisMessage.body());
}
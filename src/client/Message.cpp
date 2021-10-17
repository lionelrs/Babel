/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** Message
*/

#include "Message.hpp"

/**
 * Creates an instance of Message.
 */
Message::Message()
{
}

Message::~Message()
{
}

Message::Message(const Message &other)
{
    _body = other._body;
    _header = other._header;
}

Message::Message(const QString &body, const QString &header)
{
    _body = body;
    _header = header;
}

/**
 * Getter of message body.
 */
QString Message::getBody() const
{
    return _body;
}

/**
 * Getter of the message header.
 */
QString Message::getHeader() const
{
    return _header;
}
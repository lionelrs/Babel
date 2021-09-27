/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** Message
*/

#include "Message.hpp"

Message::Message()
{
}

Message::~Message()
{
}

Message::Message(const Message &other)
{
    m_body = other.m_body;
    m_headers = other.m_headers;
}

Message::Message(const QString &body, const QStringList &headers)
{
    m_body = body;
    m_headers = headers;
}

QString Message::body() const
{
    return m_body;
}

QStringList Message::headers() const
{
    return m_headers;
}
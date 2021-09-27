/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** Message
*/

#ifndef MESSAGE_HPP_
#define MESSAGE_HPP_

#include <QMetaType>
#include <QStringList>

class Message
{
    public:
        Message();
        Message(const Message &other);
        ~Message();

        Message(const QString &body, const QStringList &headers);

        QString body() const;
        QStringList headers() const;

    private:
        QString m_body;
        QStringList m_headers;
};

Q_DECLARE_METATYPE(Message);

#endif /* !MESSAGE_HPP_ */
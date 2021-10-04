/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** Message
*/

#ifndef MESSAGE_HPP_
#define MESSAGE_HPP_

#include <QMetaType>
#include <QString>

class Message
{
    public:
        Message();
        Message(const Message &other);
        Message(const QString &body, const QString &header);
        ~Message();

        QString getBody() const;
        QString getHeader() const;

    private:
        QString _body;
        QString _header;
};

Q_DECLARE_METATYPE(Message);

#endif /* !MESSAGE_HPP_ */
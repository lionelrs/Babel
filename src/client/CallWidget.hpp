/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** CallWidget
*/

#ifndef CALLWIDGET_HPP_
#define CALLWIDGET_HPP_

#include <QWidget>
#include <string>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class CallWidget : public QWidget {
    Q_OBJECT
    public:
        CallWidget(const std::string callerUsername, const std::string myUsername, QWidget *parent = 0);
        ~CallWidget();

        QPushButton *getButton() const;

    signals:
    public slots:
    private slots:

    protected:
    private:
        std::string _username;
        std::string _callerUsername;
        QPushButton *_hangUp;
};

#endif /* !CALLWIDGET_HPP_ */

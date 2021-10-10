/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** ErrorWidget
*/

#ifndef ERRORWIDGET_HPP_
#define ERRORWIDGET_HPP_

#include <QWidget>
#include <QMessageBox>

class ErrorWidget : public QWidget {
    Q_OBJECT
    public:
        ErrorWidget(std::string msg, std::string title, QWidget *parent = 0);
        ~ErrorWidget();

    signals:
    public slots:
    private slots:

    protected:
    private:
};

#endif /* !ERRORWIDGET_HPP_ */

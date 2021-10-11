/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** ErrorWidget
*/

#include "ErrorWidget.hpp"

ErrorWidget::ErrorWidget(std::string msg, std::string title, QWidget *parent)
{
    _msgBox = new QMessageBox(parent);
    _msgBox->setText(msg.c_str());
    _msgBox->setWindowTitle(title.c_str());

    QFont font;
    font.setPointSize(14);
    _msgBox->setFont(font);
}

ErrorWidget::~ErrorWidget()
{
}

void ErrorWidget::show()
{
    _msgBox->show();
}

void ErrorWidget::hide()
{
    _msgBox->hide();
}
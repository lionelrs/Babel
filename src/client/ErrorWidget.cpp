/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** ErrorWidget
*/

#include "ErrorWidget.hpp"

ErrorWidget::ErrorWidget(std::string msg, std::string title, QWidget *parent)
{
    QMessageBox msgBox(parent);
    msgBox.setText(msg.c_str());
    msgBox.setWindowTitle(title.c_str());
    QFont font;
    font.setPointSize(14);
    msgBox.setFont(font);
    msgBox.exec();
}

ErrorWidget::~ErrorWidget()
{
}

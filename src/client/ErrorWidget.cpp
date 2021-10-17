/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** ErrorWidget
*/

#include "ErrorWidget.hpp"

/**
 * Creates an instance of ErrorWidget.
 *
 * @param msg Error message to be displayed.
 * @param title Title to be dislayed.
 * @param parent Parent widget to herit from.
 */
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

/**
 * Show the ErrorWidget.
 */
void ErrorWidget::show()
{
    _msgBox->show();
}

/**
 * Hide the ErrorWidget.
 */
void ErrorWidget::hide()
{
    _msgBox->hide();
}
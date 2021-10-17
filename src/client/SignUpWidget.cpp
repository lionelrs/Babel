/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** SignUpWidget
*/

#include "SignUpWidget.hpp"

/**
 * Creates an instance of SignUpWidget that display the sign up form.
 *
 * @param parent Parent widget to herit from.
 */
SignUpWidget::SignUpWidget(QWidget *parent)
{
    QGroupBox *groupBox = new QGroupBox("Sign Up", parent);

    QVBoxLayout *outterLayout = new QVBoxLayout(this);
    outterLayout->addWidget(groupBox);

    QLabel *usernameLabel = new QLabel("Username", groupBox);
    _editUsername = new QLineEdit();
    QLabel *passwordLabel = new QLabel("Password", groupBox);
    _editPassword = new QLineEdit();
    _editPassword->setEchoMode(QLineEdit::Password);
    QLabel *passwordConfirmLabel = new QLabel("Confirm password", groupBox);
    _editConfirmPassword = new QLineEdit();
    _editConfirmPassword->setEchoMode(QLineEdit::Password);
    _validateButton = new QPushButton("Validate");
    _backButton = new QPushButton("Back");

    QVBoxLayout *innerLayout = new QVBoxLayout(groupBox);
    innerLayout->addWidget(usernameLabel);
    innerLayout->addWidget(_editUsername);
    innerLayout->addWidget(passwordLabel);
    innerLayout->addWidget(_editPassword);
    innerLayout->addWidget(passwordConfirmLabel);
    innerLayout->addWidget(_editConfirmPassword, 1, Qt::AlignTop);
    innerLayout->addWidget(_validateButton, 1, Qt::AlignBottom);
    innerLayout->addWidget(_backButton);

    outterLayout->setContentsMargins(QMargins(10, 0, 10, 10));
    innerLayout->setContentsMargins(QMargins(50, 50, 50, 50));

    QFont font;
    font.setPointSize(14);
    usernameLabel->setFont(font);
    groupBox->setFont(font);
    passwordLabel->setFont(font);
    _validateButton->setFont(font);
    _backButton->setFont(font);
}

SignUpWidget::~SignUpWidget()
{
}

/**
 * Getter of the filled sign up form.
 */
Message SignUpWidget::getSignUpForm()
{
    if (_editUsername->text().toStdString().find(' ') != std::string::npos)
        return Message("FORBIDDEN CHARACTER", "SPACE");
    if (_editPassword->text().toStdString().find(' ') != std::string::npos)
        return Message("FORBIDDEN CHARACTER", "SPACE");
    if (_editConfirmPassword->text().toStdString().find(' ') != std::string::npos)
        return Message("FORBIDDEN CHARACTER", "SPACE");
    if (_editConfirmPassword->text().toStdString() != _editPassword->text().toStdString())
        return Message("PASSWORDS MISMATCH", "MISMATCH");
    if (_editConfirmPassword->text().toStdString() == "" || _editPassword->text().toStdString() == ""
    || _editUsername->text().toStdString() == "")
        return Message("EMPTY FIELD", "EMPTY");
    return Message(_editUsername->text() + " " + _editPassword->text(), std::to_string(SIGN_UP).c_str());
}

/**
 * Getter of validate button.
 */
QPushButton *SignUpWidget::getValidateButton() const
{
    return _validateButton;
}

/**
 * Getter of the back button.
 */
QPushButton *SignUpWidget::getBackButton() const
{
    return _backButton;
}
/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** HubWidget
*/

#include "HubWidget.hpp"

/**
 * Creates an instance of HubWidget that display the connected users.
 *
 * @param parent Parent widget to herit from.
 */
HubWidget::HubWidget(QWidget *parent)
{
    _userList = new QListWidget(parent);

    QLabel *title = new QLabel("Connected user(s)");
    _labelUsername = new QLabel();
    _callButton = new QPushButton("Call");

    QVBoxLayout *outterLayout = new QVBoxLayout(this);
    QHBoxLayout *headerLayout = new QHBoxLayout();
    headerLayout->addWidget(title);
    headerLayout->addWidget(_labelUsername, 0, Qt::AlignRight);
    outterLayout->addLayout(headerLayout);
    outterLayout->addWidget(_userList);
    outterLayout->addWidget(_callButton);

    headerLayout->setContentsMargins(QMargins(0, 0, 20, 0));

    QFont font;
    font.setPointSize(14);
    _labelUsername->setFont(font);
    title->setFont(font);
    _userList->setFont(font);
    _callButton->setFont(font);

    connect(_userList, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(onListItemClicked(QListWidgetItem *)));
    _selected = -1;
}

HubWidget::~HubWidget()
{
}

void HubWidget::onListItemClicked(QListWidgetItem* item)
{
    _selected = _userList->row(item);
}

/**
 * Add an user to the list of connected users.
 *
 * @param username Username of the user to be added.
 */
void HubWidget::addUser(std::string username)
{
    _userList->addItem(username.c_str());
}

/**
 * Remove an user to the list of connected users.
 *
 * @param username Username of the user to be removed.
 */
void HubWidget::removeUser(std::string username)
{
    int i = 0;
    for (; i < _userList->count(); i++) {
        if (_userList->item(i)->text() == QString::fromStdString(username)) {
            delete _userList->takeItem(i);
            break;
        }
    }
}

/**
 * Getter of the call button.
 */
QPushButton *HubWidget::getButton() const
{
    return _callButton;
}

/**
 * Getter of the selected state.
 */
int HubWidget::getSelected() const
{
    return _selected;
}

/**
 * Getter of the selected user.
 */
std::string HubWidget::getSelectedName() const
{
    if (_selected == -1)
        return "null";
    return _userList->item(_selected)->text().toStdString();
}

/**
 * Setter of the client username on the top right.
 *
 * @param username Username to be set.
 */
void HubWidget::setUsername(const std::string username)
{
    _labelUsername->setText(username.c_str());
}
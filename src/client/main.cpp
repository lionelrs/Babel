/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** main
*/

#include <QApplication>
#include "../common/BabelException.hpp"
#include "Controller.hpp"

int arg_check(int ac, char *argv[])
{
    if (ac < 3) throw Babel::BabelException("./babel_server ip port");
    if (std::atoi(argv[2]) < 1025 || std::atoi(argv[2]) > 65535)
        throw Babel::BabelException("Please provide a valid port (1025 to 65535)");
    return (0);
}

int main(int argc, char *argv[])
{
    try
    {
        arg_check(argc, argv);
        QApplication app(argc, argv);
        Controller controller(std::atoi(argv[2]), argv[1]);
        controller.startBabel();
        return app.exec();
    }
    catch(const Babel::BabelException& e)
    {
        std::cerr << WHERE << std::endl << "\t" << e.what() << std::endl;
        return (84);
    }
}
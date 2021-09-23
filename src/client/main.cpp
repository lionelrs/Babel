/*
** EPITECH PROJECT, 2021
** 
** File description:
** 
*/

#include <iostream>
#include <portaudio.h>
#include <opus.h>
#include <QApplication>
#include <QtWidgets>

int main(int ac, char **av)
{
	QApplication app(ac, av);
    QWidget window;
    window.resize(320, 240);
    window.show();
    window.setWindowTitle(
        QApplication::translate("fiak", "Top-level widget"));
    return app.exec();
	// PaError err = Pa_Initialize();
	// if (err != paNoError) {
	// 	return 84;
	// }
	// err = Pa_Terminate();
	std::cout << opus_encoder_get_size(1) << std::endl;
    std::cout << "coucou je compile" << std::endl;
    	return (0);
}
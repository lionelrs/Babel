/*
** EPITECH PROJECT, 2021
** 
** File description:
** 
*/

#include <iostream>
#include <portaudio.h>
#include <opus.h>

int main(int ac, char **av)
{
	PaError err = Pa_Initialize();
	if (err != paNoError) {
		return 84;
	}
	err = Pa_Terminate();
	std::cout << opus_encoder_get_size(1) << std::endl;
    std::cout << "coucou je compile" << std::endl;
    	return (0);
}

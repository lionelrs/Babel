/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** main
*/

#include "portaudio.h"
#include "stdio.h"

int main(void)
{
    PaError err = Pa_Initialize();
    if (err != paNoError)
        printf("PortAudio error: %s\n", Pa_GetErrorText(err));
    return (0);
}
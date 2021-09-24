/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** PortAudio
*/

#include "PortAudio.hpp"

Babel::PortAudio::PortAudio()
{
    _isInit = false;
    init();
    terminate();
}

Babel::PortAudio::~PortAudio()
{
}

void Babel::PortAudio::init()
{
    if (!_isInit) {
        err = Pa_Initialize();
        if (err != paNoError) {
            throw PortAudioException(
                std::string("error initializing portaudio: ") + Pa_GetErrorText(err),
                WHERE
            );
        }
    }
    _isInit = true;
}

void Babel::PortAudio::terminate()
{
    if (_isInit) {
        err = Pa_Terminate();
        if (err != paNoError) {
            throw PortAudioException(
                std::string("error terminating portaudio: ") + Pa_GetErrorText(err),
                WHERE
            );
        }
    }
    _isInit = false;
}

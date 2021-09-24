/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** PortAudio
*/

#ifndef PORTAUDIO_HPP_
#define PORTAUDIO_HPP_

#include <portaudio.h>
#include <iostream>
#include <string>
#include "PortAudioException.hpp"

namespace Babel {
    class PortAudio {
        public:
            PortAudio();
            ~PortAudio();
            void init();
            void terminate();
        private:
            PaError err;
            bool _isInit;
    };
};


#endif /* !PORTAUDIO_HPP_ */

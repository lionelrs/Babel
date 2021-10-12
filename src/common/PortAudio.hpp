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
#include <vector>
#include <cstdio>
#include <queue>
#include <map>

#include "PortAudioException.hpp"
#include "IAudio.hpp"
#include "Opus.hpp"
#include "ISoundListener.hpp"

namespace Babel {
    class PortAudio : virtual public IAudio {
        public:
            PortAudio();
            ~PortAudio();
            ICompressor &getCompressor();
            void init();
            void terminate();
            void openInputStream();
            void openOutputStream();
            void startInputStream();
            void startOutputStream();
            void closeInputStream();
            void closeOutputStream();
            void record();
            void play();
            Babel::Sound getSound();
            void setSound(const Sound &sound, const std::string &id);
        private:
            static int recordCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData);
            static int playCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData);
            ICompressor *_compressor;
            sound_t _soundBuff;
            compressed_t _compressBuff;
            int _error;
            bool _isInit;
            PaStreamParameters _inputParams;
            PaStreamParameters _outputParams;
            PaStream *_inputStream;
            PaStream *_outputStream;
            //ISoundListener *_listener;
            std::queue<sound_t> _inputBuff;
            std::map<std::string, std::queue<sound_t>> _outputBuff;
    };
};


#endif /* !PORTAUDIO_HPP_ */

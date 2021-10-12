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
#include "PortAudioException.hpp"
#include "IAudio.hpp"
#include <cstdio>
#include "Buffer.hpp"
#include "Opus.hpp"

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
            Buffer getBuffer() const;
            void setBuffer(Buffer buffer);
            CBuffer getAudioData() const;
            void setAudioData(CBuffer data);
        private:
            static int recordCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData);
            static int playCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData);
            ICompressor *_compressor;
            Buffer _buffer;
            CBuffer _audioData;
            int _error;
            bool _isInit;
            unsigned char *_compressed;
            int _numSamples;
            PaStreamParameters _inputParams;
            PaStreamParameters _outputParams;
            PaStream *_inputStream;
            PaStream *_outputStream;
    };
};


#endif /* !PORTAUDIO_HPP_ */

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
#include <QList>
#include <QByteArray>
#include "babelDefines.hpp"


namespace Babel {
    class PortAudio : virtual public IAudio {
        public:
            PortAudio();
            ~PortAudio();
            void init();
            void terminate();
            void record();
            void play();
            int getDeviceCount() const;
            std::string getDefaultInputDevice() const;
            std::string getDefaultOutputDevice() const;
            std::string getInputDevice() const;
            std::string getOutputDevice() const;
            int getMaxInputChannels() const;
            int getMaxOutputChannels() const;
            void setInputDevice(std::string deviceName);
            void setOutputDevice(std::string deviceName);
            Buffer &getBuffer();
            ICompressor &getCompressor();
            
        private:
            static int recordCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData);
            static int playCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData);
            PaStream *_stream;
            int _deviceNb;
            int _totalFrames;
            int _numSamples;
            int _numBytes;
            SAMPLE _max;
            SAMPLE _val;
            double _average;
            PaError err;
            PaStreamParameters _inputParams;
            PaStreamParameters _outputParams;
	        const PaDeviceInfo *_inputDevice;
	        const PaDeviceInfo *_outputDevice;
            bool _isInit;
            Buffer _data;
            ICompressor *_compressor;
    };
};


#endif /* !PORTAUDIO_HPP_ */

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

#define SAMPLE_RATE  (44100)
#define FRAMES_PER_BUFFER (512)
#define NUM_SECONDS     (5)
#define NUM_CHANNELS    (2)
/* #define DITHER_FLAG     (paDitherOff) */
#define DITHER_FLAG     (0) 

#define WRITE_TO_FILE   (0)

/* Select sample format. */
#if 1
#define PA_SAMPLE_TYPE  paFloat32
typedef float SAMPLE;
#define SAMPLE_SILENCE  (0.0f)
#define PRINTF_S_FORMAT "%.8f"
#elif 1
#define PA_SAMPLE_TYPE  paInt16
typedef short SAMPLE;
#define SAMPLE_SILENCE  (0)
#define PRINTF_S_FORMAT "%d"
#elif 0
#define PA_SAMPLE_TYPE  paInt8
typedef char SAMPLE;
#define SAMPLE_SILENCE  (0)
#define PRINTF_S_FORMAT "%d"
#else
#define PA_SAMPLE_TYPE  paUInt8
typedef unsigned char SAMPLE;
#define SAMPLE_SILENCE  (128)
#define PRINTF_S_FORMAT "%d"
#endif

typedef struct
{
    int frameIndex;
    int maxFrameIndex;
    std::vector<SAMPLE> recordedSamples;
} paTestData;

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
            
        private:
            void initData();
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
            paTestData _data;
            bool _isInit;
    };
};


#endif /* !PORTAUDIO_HPP_ */

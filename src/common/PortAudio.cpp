// /*
// ** EPITECH PROJECT, 2021
// ** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
// ** File description:
// ** PortAudio
// */

#include "PortAudio.hpp"
#include <stdio.h>

Babel::PortAudio::PortAudio()
{
    _compressor = new Opus();
    _error = Pa_Initialize();
    if (_error != paNoError) {
        throw PortAudioException(std::string("error initializing portaudio: ") + Pa_GetErrorText(_error));
    }
    _isInit = true;
    init();
    _compressor = nullptr;
    _numSamples = NUM_SECONDS * SAMPLE_RATE;
}

Babel::PortAudio::~PortAudio()
{
}

Babel::ICompressor &Babel::PortAudio::getCompressor()
{
    return *_compressor;
}

void Babel::PortAudio::init()
{
    _inputParams.device = Pa_GetDefaultInputDevice();
    _inputParams.channelCount = NUM_CHANNELS;
    _inputParams.sampleFormat = PA_SAMPLE_TYPE;
    _inputParams.suggestedLatency = Pa_GetDeviceInfo(_inputParams.device)->defaultLowInputLatency;
    _inputParams.hostApiSpecificStreamInfo = NULL;

    _outputParams.device = Pa_GetDefaultOutputDevice();
    _outputParams.channelCount = NUM_CHANNELS;
    _outputParams.sampleFormat = PA_SAMPLE_TYPE;
    _outputParams.suggestedLatency = Pa_GetDeviceInfo(_outputParams.device)->defaultLowOutputLatency;
    _outputParams.hostApiSpecificStreamInfo = NULL;
}

void Babel::PortAudio::terminate()
{
    if (_isInit) {
        _error = Pa_Terminate();
        if (_error != paNoError) {
            throw PortAudioException(
                std::string("error terminating portaudio: ") + Pa_GetErrorText(_error)
            );
        }
    }
    _isInit = false;
}

void Babel::PortAudio::openInputStream()
{
    _error = Pa_OpenStream(&_inputStream, &_inputParams, NULL, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, recordCallback, &_buffer);
    if (_error != paNoError) {
        terminate();
        throw PortAudioException(std::string("Failed to open input stream") + Pa_GetErrorText(_error));
    }
}

void Babel::PortAudio::openOutputStream()
{
    _error = Pa_OpenStream(&_outputStream, NULL, &_outputParams, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, playCallback, &_buffer);
    if (_error != paNoError) {
        terminate();
        throw PortAudioException(std::string("Failed to open output stream") + Pa_GetErrorText(_error));
    }
}

void Babel::PortAudio::startInputStream()
{
    _error = Pa_StartStream(_inputStream);
    if (_error != paNoError) {
        terminate();
        throw PortAudioException(std::string("Failed to start input stream") + Pa_GetErrorText(_error));
    }
}

void Babel::PortAudio::startOutputStream()
{
    _error = Pa_StartStream(_outputStream);
    if (_error != paNoError) {
        terminate();
        throw PortAudioException(std::string("Failed to start output stream") + Pa_GetErrorText(_error));
    }
}

void Babel::PortAudio::closeInputStream()
{
    _error = Pa_CloseStream(_inputStream);
    if (_error != paNoError) {
        terminate();
        throw PortAudioException(std::string("Failed to close input stream") + Pa_GetErrorText(_error));
    }
}

void Babel::PortAudio::closeOutputStream()
{
    _error = Pa_CloseStream(_outputStream);
    if (_error != paNoError) {
        terminate();
        throw PortAudioException(std::string("Failed to close output stream") + Pa_GetErrorText(_error));
    }
}

void Babel::PortAudio::record()
{
    std::cout << "Recording" << std::endl;
    openInputStream();
    startInputStream();
    while (Pa_IsStreamActive(_inputStream) == 1) {
        Pa_Sleep(1000);
        printf("index = %d\n", _buffer.getFrameIndex() ); fflush(stdout);
    }
    closeInputStream();
    std::cout << "Finished recording" << std::endl;
}

void Babel::PortAudio::play()
{
    std::cout << "Playing" << std::endl;
    _buffer.setFrameIndex(0);
    openOutputStream();
    startOutputStream();
    while (Pa_IsStreamActive(_outputStream) == 1) {
        Pa_Sleep(1000);
        printf("index = %d\n", _buffer.getFrameIndex() ); fflush(stdout);
    }
    closeOutputStream();
    std::cout << "Finished playing" << std::endl;
}

Babel::Buffer Babel::PortAudio::getBuffer() const
{
    return _buffer;
}

void Babel::PortAudio::setBuffer(Buffer buffer)
{
    _buffer = buffer;
}

Babel::CBuffer Babel::PortAudio::getAudioData() const
{
    return _audioData;
}

void Babel::PortAudio::setAudioData(CBuffer data)
{
    _audioData = data;
}

int Babel::PortAudio::recordCallback(const void *inputBuffer, void *outputBuffer,
                               unsigned long framesPerBuffer,
                               const PaStreamCallbackTimeInfo* timeInfo,
                               PaStreamCallbackFlags statusFlags,
                               void *userData)
{
    Buffer *data = (Buffer*)userData;
    const SAMPLE *rptr = (const SAMPLE*)inputBuffer;
    SAMPLE *wptr = &data->data()[data->getFrameIndex() * NUM_CHANNELS];
    long framesToCalc;
    long i;
    int finished;
    unsigned long framesLeft = data->getMaxFrameIndex() - data->getFrameIndex();  
    (void)outputBuffer;
    (void)timeInfo;
    (void)statusFlags;
    (void)userData;    
    if (framesLeft < framesPerBuffer) {
        framesToCalc = framesLeft;
        finished = paComplete;
    }
    else {
        framesToCalc = framesPerBuffer;
        finished = paContinue;
    }
    if (inputBuffer == NULL) {
        for (i = 0; i < framesToCalc; i++) {
            *wptr++ = SAMPLE_SILENCE;  /* left */
            if (NUM_CHANNELS == 2) *wptr++ = SAMPLE_SILENCE;  /* right */
        }
    }
    else {
        for (i = 0; i < framesToCalc; i++) {
            *wptr++ = *rptr++;  /* left */
            if (NUM_CHANNELS == 2) *wptr++ = *rptr++;  /* right */
        }
    }
    data->setFrameIndex(data->getFrameIndex() + framesToCalc);
    return finished;
}

int Babel::PortAudio::playCallback(const void *inputBuffer, void *outputBuffer,
                          unsigned long framesPerBuffer,
                          const PaStreamCallbackTimeInfo* timeInfo,
                          PaStreamCallbackFlags statusFlags,
                          void *userData)
{
    Buffer *data = (Buffer*)userData;
    SAMPLE *rptr = &data->data()[data->getFrameIndex() * NUM_CHANNELS];
    SAMPLE *wptr = (SAMPLE*)outputBuffer;
    unsigned int i;
    int finished;
    unsigned int framesLeft = data->getMaxFrameIndex() - data->getFrameIndex();   
    (void)inputBuffer; /* Prevent unused variable warnings. */
    (void)timeInfo;
    (void)statusFlags;
    (void)userData;    
    if (framesLeft < framesPerBuffer) {
        /* final buffer... */
        for (i = 0; i < framesLeft; i++) {
            *wptr++ = *rptr++;  /* left */
            if (NUM_CHANNELS == 2) *wptr++ = *rptr++;  /* right */
        }
        for (; i < framesPerBuffer; i++) {
            *wptr++ = 0;  /* left */
            if (NUM_CHANNELS == 2) *wptr++ = 0;  /* right */
        }
        data->setFrameIndex(data->getFrameIndex() + framesLeft);
        finished = paComplete;
    }
    else {
        for (i = 0; i < framesPerBuffer; i++) {
            *wptr++ = *rptr++;  /* left */
            if (NUM_CHANNELS == 2) *wptr++ = *rptr++;  /* right */
        }
        data->setFrameIndex(data->getFrameIndex() + framesPerBuffer);
        finished = paContinue;
    }
    return finished;
}

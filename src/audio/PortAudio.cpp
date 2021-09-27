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
    initData();
    init();
    std::cout << getDeviceCount() << std::endl;
    std::cout << getDefaultInputDevice() << std::endl;
    std::cout << getDefaultOutputDevice() << std::endl;
    _deviceNb = getDeviceCount();
	if (_deviceNb < 0) {
        terminate();
	    throw PortAudioException(std::string("Failed to get devices"));
	}
    else if (_deviceNb == 0) {
        terminate();
	    throw PortAudioException(std::string("No devices found"));
    }
    else {
        std::cout << _deviceNb << std::endl;
        initData();
        setInputDevice("default");
        record();
        FILE  *fid;
        fid = fopen("recorded.raw", "wb");
        if( fid == NULL )
        {
            printf("Could not open file.");
        }
        else
        {
            fwrite(&_data.recordedSamples, NUM_CHANNELS * sizeof(SAMPLE), _totalFrames, fid );
            fclose( fid );
            printf("Wrote data to 'recorded.raw'\n");
        }
        _data.frameIndex = 0;
        setOutputDevice("default");
        play();

    }
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
            terminate();
            throw PortAudioException(std::string("error initializing portaudio: ") + Pa_GetErrorText(err));
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
                std::string("error terminating portaudio: ") + Pa_GetErrorText(err)
            );
        }
    }
    _isInit = false;
}

void Babel::PortAudio::record()
{
    err = Pa_OpenStream(&_stream, &_inputParams, NULL, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, recordCallback, &_data);
    if (err != paNoError) {
        terminate();
        throw PortAudioException(std::string("Failed to open stream") + Pa_GetErrorText(err));
    }
    err = Pa_StartStream(_stream);
    if (err != paNoError) {
        terminate();
        throw PortAudioException(std::string("Failed to start stream") + Pa_GetErrorText(err));
    }
    std::cout << "\n=;== Now recording!! Please speak into the microphone. ===\n";
    while ((err = Pa_IsStreamActive(_stream)) == 1) {
        Pa_Sleep(1000);
        printf("index = %d\n", _data.frameIndex ); fflush(stdout);
    }
    if (err < 0) {
        terminate();
        exit(84);
    }
    err = Pa_CloseStream(_stream);
    if (err != paNoError ) {
        terminate();
        throw PortAudioException(std::string("Failed to close stream") + Pa_GetErrorText(err));
    }
}

void Babel::PortAudio::play()
{
    _data.frameIndex = 0;
    std::cout << "\n=== Now playing back. ===\n";
    err = Pa_OpenStream(&_stream, NULL, &_outputParams, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, playCallback, &_data);
    if  (err != paNoError) {
        terminate();
        throw PortAudioException(std::string("Failed to open stream") + Pa_GetErrorText(err));
    }
    if (_stream) {
        err = Pa_StartStream(_stream);
        if  (err != paNoError) {
            terminate();
            throw PortAudioException(std::string("Failed to start stream") + Pa_GetErrorText(err));
        }
        printf("Waiting for playback to finish.\n"); fflush(stdout);
        while ((err = Pa_IsStreamActive(_stream)) == 1)
            Pa_Sleep(100);
        if (err < 0) {
            terminate();
            exit(84);
        }
        err = Pa_CloseStream(_stream);
        if  (err != paNoError) {
            terminate();
            throw PortAudioException(std::string("Failed to close stream") + Pa_GetErrorText(err));
        }

        printf("Done.\n"); fflush(stdout);
    }
}

int Babel::PortAudio::getDeviceCount() const
{
    int nbDevices = Pa_GetDeviceCount();
    return nbDevices;
}

std::string Babel::PortAudio::getDefaultInputDevice() const
{
    std::string name = static_cast<std::string>(Pa_GetDeviceInfo(Pa_GetDefaultInputDevice())->name);
    return name;
}

std::string Babel::PortAudio::getDefaultOutputDevice() const
{
    std::string name = static_cast<std::string>(Pa_GetDeviceInfo(Pa_GetDefaultOutputDevice())->name);
    return name;
}

std::string Babel::PortAudio::getInputDevice() const
{
    std::string name = static_cast<std::string>(Pa_GetDeviceInfo(_inputParams.device)->name);
    return name;
}

std::string Babel::PortAudio::getOutputDevice() const
{
    std::string name = static_cast<std::string>(Pa_GetDeviceInfo(_outputParams.device)->name);
    return name;
}

int Babel::PortAudio::getMaxInputChannels() const
{
    return Pa_GetDeviceInfo(_inputParams.device)->maxInputChannels;
}

int Babel::PortAudio::getMaxOutputChannels() const
{
    return Pa_GetDeviceInfo(_outputParams.device)->maxOutputChannels;
}

void Babel::PortAudio::setInputDevice(std::string deviceName)
{
    if (deviceName == "default")
        _inputParams.device = Pa_GetDefaultInputDevice();
    else {
        const PaDeviceInfo *deviceInfo;
        for (size_t i = 0; i < getDeviceCount(); i++) {
            deviceInfo = Pa_GetDeviceInfo(i);
            if (std::string(deviceInfo->name) == deviceName)
                _inputParams.device = i;
        }
    }
    if (_inputParams.device == paNoDevice) {
        terminate();
        throw PortAudioException(std::string("No default input device") + Pa_GetErrorText(err));
    }
    _inputParams.channelCount = 2;
    _inputParams.sampleFormat = PA_SAMPLE_TYPE;
    _inputParams.suggestedLatency = Pa_GetDeviceInfo(_inputParams.device)->defaultLowInputLatency;
    _inputParams.hostApiSpecificStreamInfo = NULL;
}

void Babel::PortAudio::setOutputDevice(std::string deviceName)
{
    if (deviceName == "default")
        _outputParams.device = Pa_GetDefaultInputDevice();
    else {
        const PaDeviceInfo *deviceInfo;
        for (size_t i = 0; i < getDeviceCount(); i++) {
            deviceInfo = Pa_GetDeviceInfo(i);
            if (std::string(deviceInfo->name) == deviceName)
                _outputParams.device = i;
        }
    }
    if (_outputParams.device == paNoDevice) {
        terminate();
        throw PortAudioException(std::string("No default output device") + Pa_GetErrorText(err));
    }
    _outputParams.channelCount = 2;
    _outputParams.sampleFormat = PA_SAMPLE_TYPE;
    _outputParams.suggestedLatency = Pa_GetDeviceInfo(_outputParams.device)->defaultLowInputLatency;
    _outputParams.hostApiSpecificStreamInfo = NULL;
}

void Babel::PortAudio::initData()
{
    _data.maxFrameIndex = _totalFrames = NUM_SECONDS * SAMPLE_RATE; /* Record for a few seconds. */
    _data.frameIndex = 0;
    _numSamples = _totalFrames * NUM_CHANNELS;

    for (size_t i = 0; i < _numSamples; i++) {
        SAMPLE tmp = 0;
        _data.recordedSamples.push_back(tmp);
    }
    
}

int Babel::PortAudio::recordCallback(const void *inputBuffer, void *outputBuffer,
                               unsigned long framesPerBuffer,
                               const PaStreamCallbackTimeInfo* timeInfo,
                               PaStreamCallbackFlags statusFlags,
                               void *userData)
{
    paTestData *data = static_cast<paTestData*>(userData);
    const SAMPLE *rptr = (const SAMPLE *)inputBuffer;
    SAMPLE *wptr = &data->recordedSamples[data->frameIndex * NUM_CHANNELS];
    long framesToCalc;
    long i;
    int finished;
    unsigned long framesLeft = data->maxFrameIndex - data->frameIndex;
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
    data->frameIndex += framesToCalc;
    return finished;
}

int Babel::PortAudio::playCallback(const void *inputBuffer, void *outputBuffer,
                          unsigned long framesPerBuffer,
                          const PaStreamCallbackTimeInfo* timeInfo,
                          PaStreamCallbackFlags statusFlags,
                          void *userData)
{
    paTestData *data = static_cast<paTestData *>(userData);
    SAMPLE *rptr = &data->recordedSamples[data->frameIndex * NUM_CHANNELS];
    SAMPLE *wptr = (SAMPLE*)outputBuffer;
    unsigned int i;
    int finished;
    unsigned int framesLeft = data->maxFrameIndex - data->frameIndex;
    (void)inputBuffer;
    (void)timeInfo;
    (void)statusFlags;
    (void)userData;
    if (framesLeft < framesPerBuffer) {
        for(i = 0; i < framesLeft; i++) {
            *wptr++ = *rptr++;  /* left */
            if (NUM_CHANNELS == 2) *wptr++ = *rptr++;  /* right */
        }
        for(; i < framesPerBuffer; i++) {
            *wptr++ = 0;  /* left */
            if (NUM_CHANNELS == 2) *wptr++ = 0;  /* right */
        }
        data->frameIndex += framesLeft;
        finished = paComplete;
    }
    else {
        for (i = 0; i < framesPerBuffer; i++) {
            *wptr++ = *rptr++;  /* left */
            if (NUM_CHANNELS == 2) *wptr++ = *rptr++;  /* right */
        }
        data->frameIndex += framesPerBuffer;
        finished = paContinue;
    }
    return finished;
}
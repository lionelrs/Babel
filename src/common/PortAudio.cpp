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
    //_listener = listener;
    _isInit = true;
    init();
}

Babel::PortAudio::~PortAudio()
{
    if (!Pa_IsStreamStopped(_inputStream))
        closeInputStream();
    if (!Pa_IsStreamStopped(_outputStream))
        closeOutputStream();
    terminate();
}

Babel::ICompressor &Babel::PortAudio::getCompressor()
{
    return *_compressor;
}

void Babel::PortAudio::init()
{
    _inputParams.device = Pa_GetDefaultInputDevice();
    if (_inputParams.device == paNoDevice)
        throw PortAudioException("Failed to get default input device.");
    _inputParams.channelCount = NUM_CHANNELS;
    _inputParams.sampleFormat = paFloat32;
    _inputParams.suggestedLatency = Pa_GetDeviceInfo(_inputParams.device)->defaultLowInputLatency;
    _inputParams.hostApiSpecificStreamInfo = nullptr;

    _outputParams.device = Pa_GetDefaultOutputDevice();
    if (_outputParams.device == paNoDevice)
        throw PortAudioException("Failed to get default output device.");
    _outputParams.channelCount = NUM_CHANNELS;
    _outputParams.sampleFormat = paFloat32;
    _outputParams.suggestedLatency = Pa_GetDeviceInfo(_outputParams.device)->defaultLowOutputLatency;
    _outputParams.hostApiSpecificStreamInfo = nullptr;
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
    _error = Pa_OpenStream(&_inputStream, &_inputParams, nullptr, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, recordCallback, this);
    if (_error != paNoError)
        throw PortAudioException(std::string("Failed to open input stream") + Pa_GetErrorText(_error));
}

void Babel::PortAudio::openOutputStream()
{
    _error = Pa_OpenStream(&_outputStream, nullptr, &_outputParams, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, playCallback, this);
    if (_error != paNoError)
        throw PortAudioException(std::string("Failed to open output stream") + Pa_GetErrorText(_error));
}

void Babel::PortAudio::startInputStream()
{
    _error = Pa_StartStream(_inputStream);
    if (_error != paNoError)
        throw PortAudioException(std::string("Failed to start input stream") + Pa_GetErrorText(_error));
}

void Babel::PortAudio::startOutputStream()
{
    _error = Pa_StartStream(_outputStream);
    if (_error != paNoError)
        throw PortAudioException(std::string("Failed to start output stream") + Pa_GetErrorText(_error));
}

void Babel::PortAudio::closeInputStream()
{
    std::queue<Sound> empty = {};
    _inputBuff.swap(empty);
    _error = Pa_CloseStream(_inputStream);
    if (_error != paNoError) {
        throw PortAudioException(std::string("Failed to close input stream") + Pa_GetErrorText(_error));
    }
}

void Babel::PortAudio::closeOutputStream()
{
    _outputBuff.clear();
    _error = Pa_CloseStream(_outputStream);
    if (_error != paNoError) {
        throw PortAudioException(std::string("Failed to close output stream") + Pa_GetErrorText(_error));
    }
}

Babel::Sound Babel::PortAudio::getSound()
{
    auto top = _inputBuff.front();

    this->_inputBuff.pop();
    return top;
}

void Babel::PortAudio::setSound(const Sound &sound, const std::string &id)
{
    _outputBuff[id].push(sound);
}

void Babel::PortAudio::record()
{
    std::cout << "Recording" << std::endl;
    openInputStream();
    startInputStream();
    while (Pa_IsStreamActive(_inputStream) == 1) {
        Pa_Sleep(1000);
    }
    closeInputStream();
    std::cout << "Finished recording" << std::endl;
}

void Babel::PortAudio::play()
{
    std::cout << "Playing" << std::endl;
    openOutputStream();
    startOutputStream();
    while (Pa_IsStreamActive(_outputStream) == 1) {
        Pa_Sleep(1000);
    }
    closeOutputStream();
    std::cout << "Finished playing" << std::endl;
}

int Babel::PortAudio::recordCallback(const void *inputBuffer, void *outputBuffer,
                               unsigned long framesPerBuffer,
                               const PaStreamCallbackTimeInfo* timeInfo,
                               PaStreamCallbackFlags statusFlags,
                               void *userData)
{
    auto sound = static_cast<PortAudio *>(userData);
    auto input = static_cast<const float *>(inputBuffer);

    sound->_inputBuff.push({ input });
    //sound->_listener->onSoundInputAvailable();
    return paContinue;
}

int Babel::PortAudio::playCallback(const void *inputBuffer, void *outputBuffer,
                          unsigned long framesPerBuffer,
                          const PaStreamCallbackTimeInfo* timeInfo,
                          PaStreamCallbackFlags statusFlags,
                          void *userData)
{
    auto sound = static_cast<PortAudio *>(userData);
    auto output = static_cast<float *>(outputBuffer);

    std::memset(output, 0, ELEM_PER_BUFFER * sizeof(float));
    for (auto it = sound->_outputBuff.begin(); it != sound->_outputBuff.end();) {
        auto &pair = *it;

        ++it;
        if (pair.second.empty()) {
            sound->_outputBuff.erase(pair.first);
            continue;
        }

        auto &soundBuffer = pair.second.front();

        for (int i = 0; i < ELEM_PER_BUFFER; ++i) {
            output[i] += soundBuffer.samples[i];
        }
        pair.second.pop();
    }
    return paContinue;
}

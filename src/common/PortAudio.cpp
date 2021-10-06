// /*
// ** EPITECH PROJECT, 2021
// ** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
// ** File description:
// ** PortAudio
// */

// #include "PortAudio.hpp"

// Babel::PortAudio::PortAudio()
// {
//     _compressor = new Opus();
//     _isInit = false;
// }

// Babel::PortAudio::~PortAudio()
// {
//     terminate();
// }

// void Babel::PortAudio::init()
// {
//     if (!_isInit) {
//         err = Pa_Initialize();
//         if (err != paNoError) {
//             terminate();
//             throw PortAudioException(std::string("error initializing portaudio: ") + Pa_GetErrorText(err));
//         }
//     }
//     _isInit = true;
//     setInputDevice("default");
//     setOutputDevice("default");
// }

// void Babel::PortAudio::terminate()
// {
//     if (_isInit) {
//         err = Pa_Terminate();
//         if (err != paNoError) {
//             throw PortAudioException(
//                 std::string("error terminating portaudio: ") + Pa_GetErrorText(err)
//             );
//         }
//     }
//     _isInit = false;
// }

// void Babel::PortAudio::record()
// {
//     err = Pa_OpenStream(&_stream, &_inputParams, NULL, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, recordCallback, &_data);
//     if (err != paNoError) {
//         terminate();
//         throw PortAudioException(std::string("Failed to open stream") + Pa_GetErrorText(err));
//     }
//     err = Pa_StartStream(_stream);
//     if (err != paNoError) {
//         terminate();
//         throw PortAudioException(std::string("Failed to start stream") + Pa_GetErrorText(err));
//     }
//     std::cout << "\n=;== Now recording!! Please speak into the microphone. ===\n";
//     while ((err = Pa_IsStreamActive(_stream)) == 1) {
//         Pa_Sleep(1000);
//         printf("index = %d\n", _data.getFrameIndex() ); fflush(stdout);
//     }
//     if (err < 0) {
//         terminate();
//         exit(84);
//     }
//     err = Pa_CloseStream(_stream);
//     if (err != paNoError ) {
//         terminate();
//         throw PortAudioException(std::string("Failed to close stream") + Pa_GetErrorText(err));
//     }
// }

// void Babel::PortAudio::play()
// {
//     _data.setFrameIndex(0);
//     std::cout << "\n=== Now playing back. ===\n";
//     err = Pa_OpenStream(&_stream, NULL, &_outputParams, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, playCallback, &_data);
//     if  (err != paNoError) {
//         terminate();
//         throw PortAudioException(std::string("Failed to open stream") + Pa_GetErrorText(err));
//     }
//     if (_stream) {
//         err = Pa_StartStream(_stream);
//         if  (err != paNoError) {
//             terminate();
//             throw PortAudioException(std::string("Failed to start stream") + Pa_GetErrorText(err));
//         }
//         printf("Waiting for playback to finish.\n"); fflush(stdout);
//         while ((err = Pa_IsStreamActive(_stream)) == 1) {
//             Pa_Sleep(1000);
//             printf("index = %d\n", _data.getFrameIndex() ); fflush(stdout);
//         }
//         if (err < 0) {
//             terminate();
//             exit(84);
//         }
//         err = Pa_CloseStream(_stream);
//         if  (err != paNoError) {
//             terminate();
//             throw PortAudioException(std::string("Failed to close stream") + Pa_GetErrorText(err));
//         }

//         printf("Done.\n"); fflush(stdout);
//     }
// }

// int Babel::PortAudio::getDeviceCount() const
// {
//     int nbDevices = Pa_GetDeviceCount();
//     return nbDevices;
// }

// std::string Babel::PortAudio::getDefaultInputDevice() const
// {
//     std::string name = static_cast<std::string>(Pa_GetDeviceInfo(Pa_GetDefaultInputDevice())->name);
//     return name;
// }

// std::string Babel::PortAudio::getDefaultOutputDevice() const
// {
//     std::string name = static_cast<std::string>(Pa_GetDeviceInfo(Pa_GetDefaultOutputDevice())->name);
//     return name;
// }

// std::string Babel::PortAudio::getInputDevice() const
// {
//     std::string name = static_cast<std::string>(Pa_GetDeviceInfo(_inputParams.device)->name);
//     return name;
// }

// std::string Babel::PortAudio::getOutputDevice() const
// {
//     std::string name = static_cast<std::string>(Pa_GetDeviceInfo(_outputParams.device)->name);
//     return name;
// }

// int Babel::PortAudio::getMaxInputChannels() const
// {
//     return Pa_GetDeviceInfo(_inputParams.device)->maxInputChannels;
// }

// int Babel::PortAudio::getMaxOutputChannels() const
// {
//     return Pa_GetDeviceInfo(_outputParams.device)->maxOutputChannels;
// }

// void Babel::PortAudio::setInputDevice(std::string deviceName)
// {
//     if (deviceName == "default")
//         _inputParams.device = Pa_GetDefaultInputDevice();
//     else {
//         const PaDeviceInfo *deviceInfo;
//         for (size_t i = 0; i < getDeviceCount(); i++) {
//             deviceInfo = Pa_GetDeviceInfo(i);
//             if (std::string(deviceInfo->name) == deviceName)
//                 _inputParams.device = i;
//         }
//     }
//     if (_inputParams.device == paNoDevice) {
//         terminate();
//         throw PortAudioException(std::string("No default input device") + Pa_GetErrorText(err));
//     }
//     _inputParams.channelCount = 2;
//     _inputParams.sampleFormat = PA_SAMPLE_TYPE;
//     _inputParams.suggestedLatency = Pa_GetDeviceInfo(_inputParams.device)->defaultLowInputLatency;
//     _inputParams.hostApiSpecificStreamInfo = NULL;
// }

// void Babel::PortAudio::setOutputDevice(std::string deviceName)
// {
//     if (deviceName == "default")
//         _outputParams.device = Pa_GetDefaultInputDevice();
//     else {
//         const PaDeviceInfo *deviceInfo;
//         for (size_t i = 0; i < getDeviceCount(); i++) {
//             deviceInfo = Pa_GetDeviceInfo(i);
//             if (std::string(deviceInfo->name) == deviceName)
//                 _outputParams.device = i;
//         }
//     }
//     if (_outputParams.device == paNoDevice) {
//         terminate();
//         throw PortAudioException(std::string("No default output device") + Pa_GetErrorText(err));
//     }
//     _outputParams.channelCount = 2;
//     _outputParams.sampleFormat = PA_SAMPLE_TYPE;
//     _outputParams.suggestedLatency = Pa_GetDeviceInfo(_outputParams.device)->defaultLowInputLatency;
//     _outputParams.hostApiSpecificStreamInfo = NULL;
// }

// Babel::Buffer &Babel::PortAudio::getBuffer()
// {
//     return _data;
// }

// Babel::ICompressor &Babel::PortAudio::getCompressor()
// {
//     return *_compressor;
// }

// int Babel::PortAudio::recordCallback(const void *inputBuffer, void *outputBuffer,
//                                unsigned long framesPerBuffer,
//                                const PaStreamCallbackTimeInfo* timeInfo,
//                                PaStreamCallbackFlags statusFlags,
//                                void *userData)
// {
//     Buffer *data = static_cast<Buffer *>(userData);
//     const SAMPLE *rptr = (const SAMPLE*)inputBuffer;
//     SAMPLE *wptr = &data->getBuffer()[data->getFrameIndex() * NUM_CHANNELS];
//     long framesToCalc;
//     long i;
//     int finished;
//     unsigned long framesLeft = data->getMaxFrameIndex() - data->getFrameIndex();  
//     (void)outputBuffer; /* Prevent unused variable warnings. */
//     (void)timeInfo;
//     (void)statusFlags;
//     (void)userData;    
//     if (framesLeft < framesPerBuffer) {
//         framesToCalc = framesLeft;
//         finished = paComplete;
//     } else {
//         framesToCalc = framesPerBuffer;
//         finished = paContinue;
//     }
//     if (inputBuffer == nullptr) {
//         for (i = 0; i < framesToCalc; i++) {
//             *wptr++ = SAMPLE_SILENCE;  /* left */
//             if (NUM_CHANNELS == 2) *wptr++ = SAMPLE_SILENCE;  /* right */
//         }
//     } else {
//         for (i = 0; i < framesToCalc; i++) {
//             *wptr++ = *rptr++;  /* left */
//             if (NUM_CHANNELS == 2) *wptr++ = *rptr++;  /* right */
//         }
//     }
//     data->setFrameIndex(data->getFrameIndex() + framesToCalc);
//     if (finished == paComplete)
//         data->setSize(data->getFrameIndex() + 1);
//     return finished;
// }

// int Babel::PortAudio::playCallback(const void *inputBuffer, void *outputBuffer,
//                           unsigned long framesPerBuffer,
//                           const PaStreamCallbackTimeInfo* timeInfo,
//                           PaStreamCallbackFlags statusFlags,
//                           void *userData)
// {
//     Buffer *data = static_cast<Buffer *>(userData);
//     SAMPLE *rptr = &data->getBuffer()[data->getFrameIndex() * NUM_CHANNELS];
//     SAMPLE *wptr = (SAMPLE*)outputBuffer;
//     unsigned int i;
//     int finished;
//     unsigned int framesLeft = data->getMaxFrameIndex() - data->getFrameIndex();   
//     (void)inputBuffer; /* Prevent unused variable warnings. */
//     (void)timeInfo;
//     (void)statusFlags;
//     (void)userData;    
//     if (framesLeft < framesPerBuffer) {
//         /* final buffer... */
//         for (i = 0; i < framesLeft; i++) {
//             *wptr++ = *rptr++;  /* left */
//             if (NUM_CHANNELS == 2) *wptr++ = *rptr++;  /* right */
//         }
//         for (; i < framesPerBuffer; i++) {
//             *wptr++ = 0;  /* left */
//             if (NUM_CHANNELS == 2) *wptr++ = 0;  /* right */
//         }
//         data->setFrameIndex(data->getFrameIndex() + framesLeft);
//         finished = paComplete;
//     } else {
//         for (i = 0; i < framesPerBuffer; i++) {
//             *wptr++ = *rptr++;  /* left */
//             if (NUM_CHANNELS == 2) *wptr++ = *rptr++;  /* right */
//         }
//         data->setFrameIndex(data->getFrameIndex() + framesPerBuffer);
//         finished = paContinue;
//     }
//     return finished;
// }
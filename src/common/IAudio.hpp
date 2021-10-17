/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** IAudio
*/

#ifndef IAUDIO_HPP_
#define IAUDIO_HPP_

#include <string>
#include "Buffer.hpp"
#include "ICompressor.hpp"
#include "CBuffer.hpp"

namespace Babel {
    class IAudio {
        public:
            virtual ~IAudio() = default;
            /**
             * Returns an instance of ICompressor 
            */
            virtual ICompressor &getCompressor() = 0;
            /**
             * Inits input and output devices from default devices
            */
            virtual void init() = 0;
            /**
             * Terminates audio library
            */
            virtual void terminate() = 0;
            /**
             * Opens an input stream
            */
            virtual void openInputStream() = 0;
            /**
             * Opens an output stream
            */
            virtual void openOutputStream() = 0;
            /**
             * Starts the input stream
            */
            virtual void startInputStream() = 0;
            /**
             * Starts the output stream
            */
            virtual void startOutputStream() = 0;
            /**
             * Closes the input stream
            */
            virtual void closeInputStream() = 0;
            /**
             * Closes the output stream
            */
            virtual void closeOutputStream() = 0;
            /**
             * Records for 20 milliseconds
            */
            virtual void record() = 0;
            /**
             * Plays recorded audio
            */
            virtual void play() = 0;
            /**
             * Returns raw audio buffer
             * Raw audio buffer is a Buffer class
            */
            virtual Buffer getBuffer() const = 0;
            /**
             * Sets raw audio data to the value of @param buffer
            */
            virtual void setBuffer(Buffer buffer) = 0;
            /**
             * Returns compressed audio data
             * Compressed audio data is a CBuffer class
            */
            virtual CBuffer getAudioData() const = 0;
            /**
             * Sets compressed data to the value of @param data
            */
            virtual void setAudioData(CBuffer data) = 0;
        private:
    };
}

#endif /* !IAUDIO_HPP_ */

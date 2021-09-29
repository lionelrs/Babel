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

namespace Babel {
    class IAudio {
        public:
            virtual ~IAudio() = default;
            virtual void init() = 0;
            virtual void terminate() = 0;
            virtual void record() = 0;
            virtual void play() = 0;
            virtual int getDeviceCount() const = 0;
            virtual std::string getDefaultInputDevice() const = 0;
            virtual std::string getDefaultOutputDevice() const = 0;
            virtual std::string getInputDevice() const = 0;
            virtual std::string getOutputDevice() const = 0;
            virtual int getMaxInputChannels() const = 0;
            virtual int getMaxOutputChannels() const = 0;
            virtual void setInputDevice(std::string deviceName) = 0;
            virtual void setOutputDevice(std::string deviceName) = 0;
            virtual Buffer &getBuffer() = 0;
        private:
    };
}

#endif /* !IAUDIO_HPP_ */

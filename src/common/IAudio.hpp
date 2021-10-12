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
            virtual ICompressor &getCompressor() = 0;
            virtual void init() = 0;
            virtual void terminate() = 0;
            virtual void openInputStream() = 0;
            virtual void openOutputStream() = 0;
            virtual void startInputStream() = 0;
            virtual void startOutputStream() = 0;
            virtual void closeInputStream() = 0;
            virtual void closeOutputStream() = 0;
            virtual void record() = 0;
            virtual void play() = 0;
        private:
    };
}

#endif /* !IAUDIO_HPP_ */

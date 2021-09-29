/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** Buffer
*/

#ifndef BUFFER_HPP_
#define BUFFER_HPP_

#include "BabelException.hpp"

#define NUM_SECONDS     (5)
#define SAMPLE_RATE  (44100)
#define NUM_CHANNELS    (2)

namespace Babel {
    class Buffer {
        public:
            Buffer();
            ~Buffer();
            SAMPLE *getBuffer() const;
            int getFrameIndex() const;
            int getMaxFrameIndex() const;
            void setFrameIndex(int idx);
            void setMaxFrameIndex(int idx);
        private:
            int _frameIndex;
            int _maxFrameIndex;
            SAMPLE *_sampleBuffer;
    };
}


#endif /* !BUFFER_HPP_ */

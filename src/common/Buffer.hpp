/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** Buffer
*/

#ifndef BUFFER_HPP_
#define BUFFER_HPP_

#include "BabelException.hpp"
#include <iostream>
#include <vector>
#include "babelDefines.hpp"

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
            void setBuffer(SAMPLE *buffer);
            void setSize(int size);
            int size() const;
        private:
            int numSamples;
            int _frameIndex;
            int _maxFrameIndex;
            // std::vector<SAMPLE> _buffer;
            SAMPLE *_sampleBuffer;
    };
}


#endif /* !BUFFER_HPP_ */

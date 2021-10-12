/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** ICompressor
*/

#ifndef ICOMPRESSOR_HPP_
#define ICOMPRESSOR_HPP_

#include "BabelException.hpp"
#include "CBuffer.hpp"
#include "Buffer.hpp"

namespace Babel {
    class ICompressor {
        public:
            ~ICompressor() = default;
            virtual CBuffer encodeFrame(const Buffer &sound) = 0;
            virtual Buffer decodeFrame(const CBuffer &compressed) = 0;
            virtual void setSampleRate(int rate) = 0;
            virtual void setNumberChannels(int nb) = 0;
            virtual int getSampleRate() const = 0;
            virtual int getNumberChannels() const = 0;
        private:
    };
}


#endif /* !ICOMPRESSOR_HPP_ */

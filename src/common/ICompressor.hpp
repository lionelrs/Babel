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
            /**
             * Takes a Buffer class @param sound to compress the raw audio data
             * Returns a CBuffer class with the compressed audio data
            */
            virtual CBuffer encodeFrame(const Buffer &sound) = 0;
            /**
             * Takes a CBuffer class @param compressed to decompress the compressed audio data
             * Returns a Buffer class with the raw audio data
            */
            virtual Buffer decodeFrame(const CBuffer &compressed) = 0;
        private:
    };
}


#endif /* !ICOMPRESSOR_HPP_ */

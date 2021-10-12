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
            virtual compressed_t encodeFrame(const sound_t &sound) = 0;
            virtual sound_t decodeFrame(const compressed_t &compressed) = 0;
        private:
    };
}


#endif /* !ICOMPRESSOR_HPP_ */

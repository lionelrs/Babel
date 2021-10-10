/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** ICompressor
*/

#ifndef ICOMPRESSOR_HPP_
#define ICOMPRESSOR_HPP_

#include "BabelException.hpp"

namespace Babel {
    class ICompressor {
        public:
            ~ICompressor() = default;
            virtual unsigned char *encodeFrame(const float *frame, int frame_size) = 0;
            virtual float *decodeFrame(const unsigned char *data, int frame_size) = 0;
        private:
    };
}


#endif /* !ICOMPRESSOR_HPP_ */

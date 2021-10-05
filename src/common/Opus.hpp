/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** Opus
*/

#ifndef OPUS_HPP_
#define OPUS_HPP_

#include "BabelException.hpp"
#include <opus.h>
#include "ICompressor.hpp"
#include "OpusException.hpp"
#include <vector>
#include "babelDefines.hpp"

namespace Babel {
    class Opus : virtual public ICompressor {
        public:
            Opus();
            ~Opus();
            unsigned char *encodeFrame(const float *frame, int frame_size);
            float *decodeFrame(const unsigned char *data, int frame_size);
            void setSampleRate(int rate);
            void setNumberChannels(int nb);
            int getSampleRate() const;
            int getNumberChannels() const;
        private:
            const std::string getError(int err) const;
            int sampleRate;
            int numChannels;
            int dataSize;
            int error;
            OpusEncoder *encoder;
            OpusDecoder *decoder;
    };
}


#endif /* !OPUS_HPP_ */

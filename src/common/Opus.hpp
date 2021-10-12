/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** Opus
*/

#ifndef OPUS_HPP_
#define OPUS_HPP_

#include <opus.h>
#include "BabelException.hpp"
#include "ICompressor.hpp"
#include "OpusException.hpp"
#include "BabelDefines.hpp"
#include "Buffer.hpp"

namespace Babel {
    class Opus : virtual public ICompressor {
        public:
            Opus();
            ~Opus();
            CBuffer encodeFrame(const Buffer &sound);
            Buffer decodeFrame(const CBuffer &compressed);
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
            int _framesPerBuffer;
            OpusEncoder *encoder;
            OpusDecoder *decoder;
    };
}


#endif /* !OPUS_HPP_ */

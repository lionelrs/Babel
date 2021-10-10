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

namespace Babel {
    class Opus : virtual public ICompressor {
        public:
            Opus();
            ~Opus();
            Babel::compressed_t encodeFrame(const sound_t &sound);
            Babel::sound_t decodeFrame(const compressed_t &compressed);

        private:
            const std::string getError(int err) const;

            int _error;
            OpusEncoder *_encoder;
            OpusDecoder *_decoder;
    };
}


#endif /* !OPUS_HPP_ */

/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** Opus
*/

#include "Opus.hpp"
#include "Buffer.hpp"
#include <iostream>

Babel::Opus::Opus()
{
    _encoder = opus_encoder_create(SAMPLE_RATE, NUM_CHANNELS, OPUS_APPLICATION_VOIP, &_error);
    if (_error != OPUS_OK)
        throw OpusException(std::string("Failed to create encoder: error ") + getError(_error));

    _decoder = opus_decoder_create(SAMPLE_RATE, NUM_CHANNELS, &_error);
    if (_error != OPUS_OK)
        throw OpusException(std::string("Failed to create decoder: error ") + getError(_error));
}

Babel::Opus::~Opus(void)
{
    if (_encoder)
        opus_encoder_destroy(_encoder);
    if (_decoder)
        opus_decoder_destroy(_decoder);
}

Babel::compressed_t Babel::Opus::encodeFrame(const sound_t &sound)
{
    compressed_t compressed;
    int size = opus_encode_float(_encoder, sound.samples.data(), FRAMES_PER_BUFFER, compressed.samples.data(), ELEM_PER_BUFFER);
    compressed.size = size;
    if (size < 0)
        throw OpusException(std::string("Failed to encode sample: ") + getError(size));
    return compressed;
}

Babel::sound_t Babel::Opus::decodeFrame(const compressed_t &compressed)
{
    sound_t sound;
    int size = opus_decode_float(_decoder, compressed.samples.data(), compressed.size, sound.samples.data(), FRAMES_PER_BUFFER, 0);
    if (size < 0)
        throw OpusException(std::string("Failed to decode sample: ") + getError(size));
    return sound;
}

const std::string Babel::Opus::getError(int err) const
{
    std::vector<std::string> errors = {"OPUS_BAD_ARG", "OPUS_BUFFER_TOO_SMALL", "OPUS_INTERNAL_ERROR",
                                        "OPUS_INVALID_PACKET", "OPUS_UNIMPLEMENTED", "OPUS_INVALID_STATE",
                                        "OPUS_ALLOC_FAIL"};
    if (err < 0 && err > -8) {
        return errors[(err * -1) - 1];
    }
    return std::string("UNKNOWN ERROR");
}

/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** Opus
*/

#include "Opus.hpp"
#include "Buffer.hpp"
#include <iostream>
#include "CBuffer.hpp"

/**
 * Creates an instance of Opus
*/
Babel::Opus::Opus()
{
    numChannels = NUM_CHANNELS;
    sampleRate = SAMPLE_RATE;
    _framesPerBuffer = FRAMES_PER_BUFFER;
    encoder = opus_encoder_create(sampleRate, numChannels, OPUS_APPLICATION_VOIP, &error);
    if (encoder == nullptr) {
        throw OpusException(std::string("Failed to create encoder: error ") + getError(error));
    }
    decoder = opus_decoder_create(sampleRate, numChannels, &error);
    if (decoder == nullptr) {
        throw OpusException(std::string("Failed to create decoder: error ") + getError(error));
    }
}

Babel::Opus::~Opus(void)
{
    if (encoder)
        opus_encoder_destroy(encoder);
    if (decoder)
        opus_decoder_destroy(decoder);
}

/**
 * Takes a Buffer class @param sound to compress the raw audio data
 * Returns a CBuffer class with the compressed audio data
*/
Babel::CBuffer Babel::Opus::encodeFrame(const Buffer &sound)
{
    CBuffer compressed;
    int size = opus_encode_float(encoder, sound.data(), FRAMES_PER_BUFFER, compressed.data().data(), ELEM_PER_BUFFER);
    compressed.setSize(size);
    if (size < 0)
        throw OpusException(std::string("Failed to encode sample: ") + getError(size));
    return compressed;
}

/**
 * Takes a CBuffer class @param compressed to decompress the compressed audio data
 * Returns a Buffer class with the raw audio data
*/
Babel::Buffer Babel::Opus::decodeFrame(const CBuffer &compressed)
{
    Buffer sound;
    int size = opus_decode_float(decoder, compressed.data().data(), compressed.size(), sound.data(), FRAMES_PER_BUFFER, 0);
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

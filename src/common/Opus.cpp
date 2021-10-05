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
    numChannels = NUM_CHANNELS;
    sampleRate = SAMPLE_RATE;
    encoder = opus_encoder_create(sampleRate, numChannels, OPUS_APPLICATION_AUDIO, &error);
    if (encoder == nullptr) {
        throw OpusException(std::string("Failed to create encoder: error ") + getError(error));
    }
    decoder = opus_decoder_create(sampleRate, numChannels, &error);
    if (decoder == nullptr) {
        throw OpusException(std::string("Failed to create decoder: error ") + getError(error));
    }
    opus_int32 rate = SAMPLE_RATE;
    opus_encoder_ctl(encoder, OPUS_GET_BANDWIDTH(&rate));
    dataSize = rate;
    std::cout << dataSize << std::endl;
}

Babel::Opus::~Opus(void)
{
    opus_encoder_destroy(encoder);
    opus_decoder_destroy(decoder);
}

unsigned char *Babel::Opus::encodeFrame(const float *frame, int frameSize)
{
    unsigned char *compressedBuffer;
    int ret;
    compressedBuffer = new unsigned char[NUM_CHANNELS * FRAME_SIZE];
    ret = opus_encode_float(encoder, frame, FRAME_SIZE, compressedBuffer, dataSize);
    if (ret < 0) {
        throw OpusException(std::string("Failed to encode sample: ") + getError(ret));
    }
    return compressedBuffer;
}

float *Babel::Opus::decodeFrame(const unsigned char *data, int frameSize)
{
    int ret;
    float *frame = new float[NUM_SECONDS * SAMPLE_RATE * NUM_CHANNELS];
    ret = opus_packet_get_nb_channels(data);
    if (ret < 0) {
        throw OpusException(std::string("Corrupted data or unsupported type: ") + getError(ret));
    }
    ret = opus_decode_float(decoder, data, dataSize, frame, frameSize, 0);
    if (ret < 0) {
        throw OpusException(std::string("Failed to decode sample: ") + getError(ret));
    }
    return frame;
}

void Babel::Opus::setSampleRate(int rate)
{
    sampleRate = rate;
}

void Babel::Opus::setNumberChannels(int nb)
{
    numChannels = nb;
}

int Babel::Opus::getSampleRate() const
{
    return sampleRate;
}

int Babel::Opus::getNumberChannels() const
{
    return numChannels;
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

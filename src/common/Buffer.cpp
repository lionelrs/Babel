/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** Buffer
*/

#include "Buffer.hpp"

Babel::Buffer::Buffer()
{
    _samples.fill(0);
    _frameIndex = 0;
    _maxFrameIndex = NUM_SECONDS * SAMPLE_RATE;
    numSamples = NUM_SECONDS * SAMPLE_RATE * NUM_CHANNELS;
    _sampleBuffer = new SAMPLE[numSamples];
    for (size_t i = 0; i < numSamples; i++) {
        _sampleBuffer[i] = 0;
    }
}

Babel::Buffer::Buffer(const float *begin)
{
    std::memcpy(_samples.data(), begin, ELEM_PER_BUFFER * sizeof(float));
}

Babel::Buffer::~Buffer()
{
}

Babel::SAMPLE *Babel::Buffer::data() const
{
    return _sampleBuffer;
}

int Babel::Buffer::getFrameIndex() const
{
    return _frameIndex;
}

int Babel::Buffer::getMaxFrameIndex() const
{
    return _maxFrameIndex;
}

void Babel::Buffer::setFrameIndex(int idx)
{
    _frameIndex = idx;
}

void Babel::Buffer::setMaxFrameIndex(int idx)
{
    _maxFrameIndex = idx;
}

void Babel::Buffer::setBuffer(SAMPLE *buffer)
{   
    std::cout << numSamples << std::endl;
    for (size_t i = 0; i < numSamples; i++) {
        _sampleBuffer[i] = buffer[i];
    }
    std::cout << "set buffer\n";
}

void Babel::Buffer::setSize(int size)
{
    numSamples = size;
}

int Babel::Buffer::size() const
{
    return numSamples;
}

std::array<float, ELEM_PER_BUFFER> Babel::Buffer::getArray() const
{
    return _samples;
}
/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** Buffer
*/

#include "Buffer.hpp"

/**
 * Creates an instance of Buffer
*/
Babel::Buffer::Buffer()
{
    _frameIndex = 0;
    _maxFrameIndex = SAMPLE_RATE / 60;
    numSamples = (SAMPLE_RATE * NUM_CHANNELS) / 60;
    _sampleBuffer = new SAMPLE[numSamples];
    for (size_t i = 0; i < numSamples; i++) {
        _sampleBuffer[i] = 0;
    }
}

Babel::Buffer::~Buffer()
{
}

/**
 * Gets the raw audio buffer
 * Returns a SAMPLE*
*/
Babel::SAMPLE *Babel::Buffer::data() const
{
    return _sampleBuffer;
}

/**
 * Gets the actual frame index
 * Returns an integer
*/
int Babel::Buffer::getFrameIndex() const
{
    return _frameIndex;
}

/**
 * Gets the maximum frame index
 * Returns an integer
*/
int Babel::Buffer::getMaxFrameIndex() const
{
    return _maxFrameIndex;
}

/**
 * Sets the actual frame index to the value of @param idx
*/
void Babel::Buffer::setFrameIndex(int idx)
{
    _frameIndex = idx;
}

/**
 * Sets the maximum frame index to the value of @param idx
*/
void Babel::Buffer::setMaxFrameIndex(int idx)
{
    _maxFrameIndex = idx;
}

/**
 * Sets the raw audio buffer to the value of @param buffer
*/
void Babel::Buffer::setBuffer(SAMPLE *buffer)
{
    std::cout << numSamples << std::endl;
    for (size_t i = 0; i < numSamples; i++) {
        _sampleBuffer[i] = buffer[i];
    }
    std::cout << "set buffer\n";
}

/**
 * Sets the buffer size to the value of @param size
*/
void Babel::Buffer::setSize(int size)
{
    numSamples = size;
}

/**
 * Gets the size of the audio buffer
 * Returns an integer
*/
int Babel::Buffer::size() const
{
    return numSamples;
}
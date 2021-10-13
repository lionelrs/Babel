/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** BabelDefines
*/

#ifndef BABELDEFINES_HPP_
#define BABELDEFINES_HPP_

#include <array>
#include <vector>
#include <cstring>

namespace Babel {

    #define NUM_SECONDS (5)
    #define NUM_CHANNELS (2)
    #define SAMPLE_RATE (48000)
    #define PA_SAMPLE_TYPE (paFloat32)
    #define SAMPLE_SILENCE (0.0f)
    #define FRAMES_PER_BUFFER (480)
    #define ELEM_PER_BUFFER (FRAMES_PER_BUFFER * NUM_CHANNELS)

    typedef struct Sound {
        std::array<float, ELEM_PER_BUFFER> samples;
        int frameIndex;
        int maxFrameIndex;
        int numSamples;
        SAMPLE *buffer;
        int size;

        Sound()
        {
            maxFrameIndex = NUM_SECONDS * SAMPLE_RATE;
            frameIndex = 0;
            numSamples = NUM_SECONDS * SAMPLE_RATE * NUM_CHANNELS;
            size = numSamples * sizeof(float);
            buffer = new SAMPLE[size];
            for (size_t i = 0; i < numSamples; i++) {
                buffer[i] = 0;
            }
            samples.fill(0);
        }

        Sound(const float *begin)
        {
            std::memcpy(samples.data(), begin, ELEM_PER_BUFFER * sizeof(float));
        }
    } sound_t;

    typedef struct Compressed {
        std::vector<unsigned char> samples;
        int32_t size;

        Compressed()
        {
            samples.resize(ELEM_PER_BUFFER);
            std::fill(samples.begin(), samples.end(), 0);
        }
    } compressed_t;
}

#endif /* !BABELDEFINES_HPP_ */

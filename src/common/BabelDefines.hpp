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
    #define FRAMES_PER_BUFFER (480)
    #define ELEM_PER_BUFFER (FRAMES_PER_BUFFER * NUM_CHANNELS)

    typedef struct Sound {
        std::array<float, ELEM_PER_BUFFER> samples;

        Sound()
        {
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

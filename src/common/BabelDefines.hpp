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
}

#endif /* !BABELDEFINES_HPP_ */

/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** babelDefines
*/

#ifndef BABELDEFINES_HPP_
#define BABELDEFINES_HPP_

#define NUM_SECONDS (5)
#define NUM_CHANNELS (2)
#define SAMPLE_RATE (48000)
#define FRAMES_PER_BUFFER (512)
#define ELEM_PER_BUFFER (FRAMES_PER_BUFFER * NUM_CHANNELS)
#define FRAME_SIZE (480)
#define PA_SAMPLE_TYPE  paFloat32
#define SAMPLE_SILENCE  (0.0f)
#define MAX_FRAME_SIZE (6*960)

#endif /* !BABELDEFINES_HPP_ */

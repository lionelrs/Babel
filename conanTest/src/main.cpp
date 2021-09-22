#include <stdio.h>
#include <math.h>
#include "portaudio.h"

int main(void)
{
    PaError err = Pa_Initialize();
    if (err != paNoError) {
        printf( "PortAudio error: %s\n", Pa_GetErrorText(err));
        return (84);
    }

    err = Pa_Terminate();
    if (err != paNoError) {
        printf("PortAudio error: %s\n", Pa_GetErrorText(err));
        return (84);
    }
    return (0);
}
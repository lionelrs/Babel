/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** IAudio
*/

#ifndef IAUDIO_HPP_
#define IAUDIO_HPP_

class IAudio {
    public:
        virtual ~IAudio() {};

        virtual void Initialization() = 0;
        virtual void PlayAudio() = 0;

    protected:
    private:
};

#endif /* !IAUDIO_HPP_ */

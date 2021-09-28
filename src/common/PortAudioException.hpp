/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** PortAudioException
*/

#ifndef PORTAUDIOEXCEPTION_HPP_
#define PORTAUDIOEXCEPTION_HPP_

#include "../common/BabelException.hpp"

namespace Babel {
    class PortAudioException : public BabelException {
        public:
            PortAudioException(const std::string &what) :BabelException(what) {};
    };
};

#endif /* !PORTAUDIOEXCEPTION_HPP_ */

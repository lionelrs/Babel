/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** OpusException
*/

#ifndef OPUSEXCEPTION_HPP_
#define OPUSEXCEPTION_HPP_

#include "../common/BabelException.hpp"

namespace Babel {
    class OpusException : public BabelException {
        public:
            OpusException(const std::string &what) :BabelException(what) {};
    };
};

#endif /* !OPUSEXCEPTION_HPP_ */

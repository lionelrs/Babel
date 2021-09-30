/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** BabelException
*/

#ifndef BABELEXCEPTION_HPP_
#define BABELEXCEPTION_HPP_

#include <exception>
#include <string>

#define WHERE ("exception at : \n\t" + std::string(__FILE__) + " l:" + std::to_string(__LINE__))

namespace Babel {
    using SAMPLE = float;
    class BabelException : public std::exception {
        public:
            BabelException(const std::string &what): _what(what) {};
            ~BabelException() override = default;
            const char *what() const noexcept override {
                return _what.c_str();
            }
        private:
            std::string _what;
    };
};

#endif /* !BABELEXCEPTION_HPP_ */

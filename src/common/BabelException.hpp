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

#define WHERE (std::string(__FILE__) + " " + std::to_string(__LINE__))

namespace Babel {
    class BabelException : public std::exception {
        public:
            BabelException(const std::string &what, const std::string &where): _what(what), _where(where) {};
            ~BabelException() override = default;
            const char *what() const noexcept override {
                return _what.c_str();
            }
            const char *where() const noexcept {
                return _where.c_str();
            }
        private:
            std::string _what;
            std::string _where;
    };
};

#endif /* !BABELEXCEPTION_HPP_ */

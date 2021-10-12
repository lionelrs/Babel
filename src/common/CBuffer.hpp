/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** CBuffer
*/

#ifndef CBUFFER_HPP_
#define CBUFFER_HPP_

#include "BabelException.hpp"
#include <iostream>
#include <vector>
#include "babelDefines.hpp"

namespace Babel {
    class CBuffer {
        public:
            CBuffer();
            ~CBuffer();
            void setData(std::vector<unsigned char> data);
            void setSize(int size);
            std::vector<unsigned char> data() const;
            int32_t size() const;
        private:
            std::vector<unsigned char> _samples;
            int32_t _size;
    };
}

#endif /* !CBUFFER_HPP_ */

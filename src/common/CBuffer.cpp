/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** CBuffer
*/

#include "CBuffer.hpp"

Babel::CBuffer::CBuffer()
{
    _samples.resize(ELEM_PER_BUFFER);
    std::fill(_samples.begin(), _samples.end(), 0);
}

Babel::CBuffer::~CBuffer()
{
}

void Babel::CBuffer::setData(std::vector<unsigned char> data)
{
    _samples = data;
}

void Babel::CBuffer::setSize(int size)
{
    _size= size;
}

std::vector<unsigned char> Babel::CBuffer::data() const
{
    return _samples;
}

int Babel::CBuffer::size() const
{
    return _samples.size();
}
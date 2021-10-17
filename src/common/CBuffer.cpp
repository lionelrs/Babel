/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** CBuffer
*/

#include "CBuffer.hpp"

/**
 * Creates an instance of CBuffer
*/
Babel::CBuffer::CBuffer()
{
    _samples.resize(ELEM_PER_BUFFER);
    std::fill(_samples.begin(), _samples.end(), 0);
}

Babel::CBuffer::~CBuffer()
{
}

/**
 * Sets the compressed sample buffer to the value of @param data
*/
void Babel::CBuffer::setData(std::vector<unsigned char> data)
{
    _samples = data;
}

/**
 * Sets the size of the compressed sample buffer to the value of @param size
*/
void Babel::CBuffer::setSize(int size)
{
    _size= size;
}

/**
 * Gets the compressed sample buffer
 * Returns std::vector<unsigned char>
*/
std::vector<unsigned char> Babel::CBuffer::data() const
{
    return _samples;
}

/**
 * Gets the compressed sample buffer size
 * Returns an integer
*/
int Babel::CBuffer::size() const
{
    return _samples.size();
}
/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** ICompressor
*/

#ifndef ICOMPRESSOR_HPP_
#define ICOMPRESSOR_HPP_

class ICompressor {
    public:
        virtual ~ICompressor() {};

        virtual void Initialization() = 0;
        virtual void Compress() = 0;
        virtual void Decompress() = 0;

    protected:
    private:
};

#endif /* !ICOMPRESSOR_HPP_ */

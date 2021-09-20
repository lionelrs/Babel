/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** INetwork
*/

#ifndef INETWORK_HPP_
#define INETWORK_HPP_

class INetwork {
    public:
        virtual ~INetwork() {};

        virtual void Initialization() = 0;
        virtual void Listen() = 0;
        virtual void Send() = 0;

    protected:
    private:
};

#endif /* !INETWORK_HPP_ */
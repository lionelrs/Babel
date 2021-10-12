/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** ISoundListener
*/

#ifndef ISOUNDLISTENER_HPP_
#define ISOUNDLISTENER_HPP_

namespace Babel
{
    class ISoundListener {
        public:
            virtual ~ISoundListener() = default;

            virtual void onSoundInputAvailable() = 0;
    };
} // namespace Babel

#endif /* !ISOUNDLISTENER_HPP_ */

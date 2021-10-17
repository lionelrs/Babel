Pour build lancer le script ./build.sh

Faites egalement les lignes ci-dessous (a potentiellement adapter)

export ALSA_CONFIG_DIR=/usr/share/alsa
export ALSA_CONFIGDIR=~/.conan/data/libalsa/1.1.9//_/package/d48130e0dd76369b1338deb3b2372c5a649f9f2d/res/alsa

ln -s /usr/lib64/alsa-lib/ ~/.conan/data/libalsa/1.1.9/_/_/package/d48130e0dd76369b1338deb3b2372c5a649f9f2d/lib/
ln -s /usr/lib64/pkgconfig/ ~/.conan/data/libalsa/1.1.9/_/_/package/d48130e0dd76369b1338deb3b2372c5a649f9f2d/lib/

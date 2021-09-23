POUR BUILD LE PROJET IL FAUT UTILISER CETTE COMMAND

mkdir build && cd build && conan install .. && cmake .. -G "Unix Makefiles" && cmake --build .

Dans le bashrc

export ALSA_CONFIG_DIR=/usr/share/alsa

ln -s /usr/lib64/alsa-lib/ ~/.conan/data/libalsa/1.1.9/_/_/package/d48130e0dd76369b1338deb3b2372c5a649f9f2d/lib/
ln -s /usr/lib64/pkgconfig/ ~/.conan/data/libalsa/1.1.9/_/_/package/d48130e0dd76369b1338deb3b2372c5a649f9f2d/lib/

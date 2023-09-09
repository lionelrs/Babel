# Babel

Babel is a client-server based Voice Over IP (VOIP) application that offers functionality akin to Skype or TeamSpeak. The software is platform-independent, working seamlessly on both Unix and Windows operating systems.

The core objective of Babel is to implement a protocol similar to SIP for Voice Over IP communication. The protocol is designed to be globally applicable, making it viable for use over the Internet without any reliance on LAN-specific features.

Voice transmission between clients relies on UDP, making it a client-to-client interaction.

## Libraries used
- [Asio](https://www.boost.org/doc/libs/1_83_0/doc/html/boost_asio.html)
- [QT](https://www.qt.io/product/framework?utm_term=c%2B%2B%20development%20software&utm_campaign=Development,+Framework+%26+Tools+%7C+TOFU&utm_source=adwords&utm_medium=ppc&hsa_acc=7519109677&hsa_net=adwords&hsa_cam=20181436461&hsa_ad=667272431694&hsa_kw=c%2B%2B%20development%20software&hsa_grp=152465491107&hsa_mt=p&hsa_ver=3&hsa_src=g&hsa_tgt=kwd-814187963930&gad=1&gclid=CjwKCAjwr_CnBhA0EiwAci5siv-GczRz3dB1ryv3ejQPuE82lPeXPtYrtYgWn3KM40xlcLuUFKYVKhoCWlQQAvD_BwE)
- [Portaudio](https://www.portaudio.com/)
- [Opus](https://opus-codec.org/)

## Building the project
To build the project, follow the commands below:

```
./build.sh
```
Set your ALSA configurations:
```
export ALSA_CONFIG_DIR=/usr/share/alsa
export ALSA_CONFIGDIR=~/.conan/data/libalsa/1.1.9//_/package/d48130e0dd76369b1338deb3b2372c5a649f9f2d/res/alsa
```
Create symbolic links:
```
ln -s /usr/lib64/alsa-lib/ ~/.conan/data/libalsa/1.1.9/_/_/package/d48130e0dd76369b1338deb3b2372c5a649f9f2d/lib/
ln -s /usr/lib64/pkgconfig/ ~/.conan/data/libalsa/1.1.9/_/_/package/d48130e0dd76369b1338deb3b2372c5a649f9f2d/lib/
```

## Documentation

Generate the code documentation using Doxygen with the provided Doxyfile:
```
doxygen Doxyfile
```

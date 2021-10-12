cmake_minimum_required( VERSION 3.10 )

project (mainDemo)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Xml REQUIRED)
set(CMAKE_AUTOMOC ON)

include(build/conanbuildinfo.cmake)
include(build/conan_paths.cmake)
conan_basic_setup(KEEP_RPATHS)

include_directories(${CONAN_INCLUDE_DIRS})

link_directories(${CONAN_LIBRARIES_DIRS})

SET(GCC_COVERAGE_COMPILE_FLAGS "-lrt -lm -lasound -ljack -pthread")

message("\n\nwoow je vais set env")

# set(ENV{ALSA_CONFIG_DIR} "~/.conan/data/libalsa/1.1.9/_/_/package/d48130e0dd76369b1338deb3b2372c5a649f9f2d/res/alsa")

message("j'ai fini \n\n")

file(GLOB CLIENT_SRC "src/client/*.cpp" "src/client/*.hpp")

file(GLOB SERVER_SRC "src/server/*.cpp" "src/server/*.hpp")

file(GLOB COMMON "src/common/*.cpp" "src/common/*.hpp")

# SET(Q_Object "src/client/MyUDP.hpp")
# QT5_WRAP_CPP(Q_OBJECT_MOC ${Q_Object})

add_executable (babel_client ${CLIENT_SRC} ${COMMON})

target_include_directories(babel_client PUBLIC ${CONAN_INCLUDE_DIRS} /src/common)
target_link_libraries(babel_client PUBLIC ${CONAN_LIBS})
target_link_libraries(babel_client PUBLIC "-lrt -lm -lasound -ljack -g3")
#find_package(Qt5Widgets CONFIG REQUIRED)
#find_package(Qt5Network CONFIG REQUIRED)
#find_package(Qt5Core CONFIG REQUIRED)
#find_package(Qt5Gui CONFIG REQUIRED)
#find_package(portaudio REQUIRED)
#find_package(Opus REQUIRED)
add_executable (babel_server ${SERVER_SRC} ${COMMON})

target_link_libraries(babel_client PUBLIC "-lrt -lm -lasound -ljack")
target_include_directories(babel_server PUBLIC ${CONAN_INCLUDE_DIRS} /src/common)
target_link_libraries(babel_server PUBLIC ${CONAN_LIBS})
target_link_libraries(babel_server PUBLIC "-pthread")

#target_link_libraries(mainDemo opus)
#target_link_libraries(babel_client Qt5::Widgets Qt5::Network Qt5::Core Qt5::Gui)

cmake_minimum_required( VERSION 3.10 )

project (mainDemo)

include(build/conanbuildinfo.cmake)
include(build/conan_paths.cmake)
conan_basic_setup(KEEP_RPATHS)

include_directories(${CONAN_INCLUDE_DIRS})
link_directories(${CONAN_LIBRARIES_DIRS})

SET(GCC_COVERAGE_COMPILE_FLAGS "-lrt -lm -lasound -ljack -pthread")

add_executable (
    babel_client
    src/client/main.cpp
)

add_executable (
    babel_server
    src/server/main.cpp
)

#find_package(Qt5Widgets CONFIG REQUIRED)
#find_package(Qt5Network CONFIG REQUIRED)
#find_package(Qt5Core CONFIG REQUIRED)
#find_package(Qt5Gui CONFIG REQUIRED)
#find_package(portaudio REQUIRED)
#find_package(Opus REQUIRED)

target_link_libraries(babel_server PUBLIC "-pthread")
target_link_libraries(babel_client PUBLIC "-lrt -lm -lasound -ljack")

target_link_libraries(babel_client PUBLIC ${CONAN_LIBS})
target_include_directories(babel_client PUBLIC ${CONAN_INCLUDE_DIRS})
#target_link_libraries(mainDemo opus)
#target_link_libraries(babel_client Qt5::Widgets Qt5::Network Qt5::Core Qt5::Gui)

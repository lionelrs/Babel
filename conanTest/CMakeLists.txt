cmake_minimum_required( VERSION 3.21.3 )
set(CMAKE_BUILD_TYPE Release)
project (mainDemo)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
conan_basic_setup(TARGETS)

include_directories(${CMAKE_INCLUDE_PATH})


add_executable (mainDemo src/main.cpp)

find_package(Opus)
find_package(portaudio)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

message("------ --- --- -- - -NOOOOOOOOOOOOOOOON- -- --  --- -- --- --\n\n\n")

include_directories(${CONAN_INCLUDE_OPUS})
include_directories(${CONAN_INCLUDE_PORTAUDIO})
include_directories(${CONAN_INCLUDE_QT5})

if(QT5_FOUND)
message("------ --- --- -- - -opus find- -- --  --- -- --- --\n\n\n")
endif()

# target_link_libraries(mainDemo ${CONAN_LIBS})
conan_target_link_libraries(mainDemo CONAN_PKG::opus)
conan_target_link_libraries(mainDemo CONAN_PKG::portaudio)
conan_target_link_libraries(mainDemo CONAN_PKG::qt)
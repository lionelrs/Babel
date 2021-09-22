cmake_minimum_required( VERSION 3.21.3 )
set(CMAKE_BUILD_TYPE Release)
project (mainDemo)

include(build/conan_paths.cmake)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
conan_basic_setup(KEEP_RPATH)

include_directories(${CMAKE_INCLUDE_PATH})


add_executable (mainDemo src/main.cpp)

# find_package(Qt5Widgets CONFIG REQUIRED)
# find_package(Qt5Network CONFIG REQUIRED)
# find_package(Qt5Core CONFIG REQUIRED)
# find_package(Qt5Gui CONFIG REQUIRED)
find_package(Opus REQUIRED)
find_package(portaudio REQUIRED)
# find_package(Qt5 COMPONENTS Core REQUIRED)

message("------ --- --- -- - -NOOOOOOOOOOOOOOOON- -- --  --- -- --- --\n\n\n")


# target_link_libraries(mainDemo opus)
# target_link_libraries(mainDemo portaudio)
# target_link_libraries(mainDemo Qt5::Widgets Qt5::Network Qt5::Core Qt5::Gui)


include_directories(${CONAN_INCLUDE_OPUS})
include_directories(${CONAN_INCLUDE_PORTAUDIO})
include_directories(${CONAN_INCLUDE_QT5})
message("boost->" ${Opus_INCLUDE_DIR})
message("opute->" ${CONAN_INCLUDE_OPUS})
message("portaudio->" ${CONAN_INCLUDE_PORTAUDIO})
message("qt5 le s->" ${CONAN_INCLUDE_DIRS_Qt5})

if(Qt5_FOUND)
message("------ --- --- -- - -QT5555 find- -- --  --- -- --- --\n\n\n")
endif()

target_include_directories(mainDemo PUBLIC ${CONAN_INCLUDE_DIRS})
conan_target_link_libraries(mainDemo CONAN_PKG::opus)
conan_target_link_libraries(mainDemo CONAN_PKG::portaudio)
conan_target_link_libraries(mainDemo CONAN_PKG::Qt5Core)

# conan_target_link_libraries(mainDemo ${CONAN_LIBS})
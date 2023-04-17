cmake_minimum_required(VERSION 3.0.0)
project(arcade VERSION 0.1.0)

include(CTest)
enable_testing()


file(GLOB_RECURSE helloworld_SRC
     "src/core/*.hpp"
     "src/core/*.cpp"
)

foreach (file ${helloworld_SRC})
    set(MYFILE_DIR)
    if (file MATCHES ".*.hpp")
        get_filename_component(MYFILE_DIR ${file} DIRECTORY)
        include_directories(${MYFILE_DIR} )
    endif()
endforeach()

file(GLOB_RECURSE rb_rpdb_src "src/arcade/")
message(STATUS "headers: ${rb_rpdb_src} ")
add_executable(arcade ${helloworld_SRC})
TARGET_LINK_LIBRARIES(arcade dl)

# LIB
project(sfml VERSION 0.1.0)
file(GLOB_RECURSE SRC_LIB
     "src/lib/SFML/*.hpp"
     "src/lib/SFML/*.cpp"
)
add_library(sfml SHARED ${SRC_LIB})
target_link_libraries(sfml sfml-graphics sfml-window sfml-system sfml-network sfml-audio)

project(ncurse VERSION 0.1.0)
file(GLOB_RECURSE SRC_LIB
     "src/lib/NCURSES/*.hpp"
     "src/lib/NCURSES/*.cpp"
)
add_library(ncurse SHARED ${SRC_LIB})
target_link_libraries(ncurse ncurses)

project(sdl VERSION 0.1.0)
file(GLOB_RECURSE SRC_LIB
     "src/lib/SDL2/*.hpp"
     "src/lib/SDL2/*.cpp"
)
add_library(sdl SHARED ${SRC_LIB})
target_link_libraries(sdl SDL2 SDL2_image SDL2_ttf)


project(nibbler VERSION 0.1.0)
file(GLOB_RECURSE SRC_NIBBLER
     "src/games/Nibbler/*.hpp"
     "src/games/Nibbler/*.cpp"
)
add_library(nibbler SHARED ${SRC_NIBBLER})
target_link_libraries(nibbler)

project(pacman VERSION 0.1.0)
file(GLOB_RECURSE SRC_PACMAN
     "src/games/Pacman/*.hpp"
     "src/games/Pacman/*.cpp"
)
add_library(pacman SHARED ${SRC_PACMAN})
target_link_libraries(pacman)

# add_custom_command(TARGET arcade POST_BUILD COMMAND mv arcade arcade)
add_custom_command(TARGET ncurse POST_BUILD COMMAND mv libncurse.so lib/arcade_ncurses.so)
add_custom_command(TARGET pacman POST_BUILD COMMAND mv libpacman.so lib/arcade_pacman.so)
add_custom_command(TARGET sdl POST_BUILD COMMAND mv libsdl.so lib/arcade_sdl2.so)
add_custom_command(TARGET sfml POST_BUILD COMMAND mv libsfml.so lib/arcade_sfml.so)
add_custom_command(TARGET nibbler POST_BUILD COMMAND mv libnibbler.so lib/arcade_nibbler.so)

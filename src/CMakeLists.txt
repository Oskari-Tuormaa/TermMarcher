cmake_minimum_required(VERSION 3.10)

# set the project name
project(Raymarcher)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})



# add the executable
add_executable(Raymarcher main.cpp)
target_link_libraries(Raymarcher ${CURSES_LIBRARIES})
target_link_libraries(Raymarcher ${X11_LIBRARIES})



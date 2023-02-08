cmake_minimum_required(VERSION 2.6)
file(TO_CMAKE_PATH "$ENV{IMAGINEPP_ROOT}/CMake" p)
list(APPEND CMAKE_MODULE_PATH "${p}") #For old Imagine++
list(APPEND CMAKE_SYSTEM_FRAMEWORK_PATH /Library/Frameworks) #Mac, why not auto?
find_package(Imagine REQUIRED)



project(ChaosFractals)

add_library(UI
    ui.cpp
    button.cpp
    text.cpp
    ui.h
    button.h
    text.h
)
ImagineUseModules(UI Graphics)



add_executable(ChaosFractals
    main.cpp
    constants.h
    simulator.cpp
    simulator.h
    math2d.cpp
    math2d.h
)
ImagineUseModules(ChaosFractals Graphics)

target_link_libraries(ChaosFractals UI)

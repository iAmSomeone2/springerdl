cmake_minimum_required(VERSION 3.10)

project(SpringerDL VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

include(GNUInstallDirs)

add_subdirectory(src)
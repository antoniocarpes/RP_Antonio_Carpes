cmake_minimum_required(VERSION 2.8.3)
project(mini_core LANGUAGES CXX)

# Configuración de C++11
set(CMAKE_CXX_STANDARD 11)  
set(CMAKE_CXX_STANDARD_REQUIRED ON) 

# TODO invokes the routines to find a package called Eigen3
find_package(Eigen3 REQUIRED)
include_directories("/opt/homebrew/opt/eigen/")
# Incluir el directorio de Eigen
include_directories(${EIGEN3_INCLUDE_DIRS})


# add project source code
add_subdirectory(src)

# TODO do the same for executables
add_subdirectory(executables)

message("-------------------- Executed! -------------------------")
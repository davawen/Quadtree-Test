cmake_minimum_required(VERSION 3.12...3.21)

# Flags / Options
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_CXX_STANDARD "17")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_NAME "qtree")

project(${PROJECT_NAME} VERSION 1.0 LANGUAGES CXX)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

add_executable(${PROJECT_NAME}
	./include/ball.hpp
	./include/freelist.hpp
	./include/qtree.hpp
	./src/main.cpp
)

# Headers
target_include_directories(${PROJECT_NAME} PRIVATE ./include)
target_include_directories(${PROJECT_NAME} PRIVATE ${SFML_INCLUDE_DIRS})

# Libraries

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

# Compilation

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	target_compile_options(${PROJECT_NAME} PRIVATE /W4)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Wno-unknown-pragmas)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
	target_compile_options(${PROJECT_NAME} PRIVATE)
endif()

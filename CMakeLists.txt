cmake_minimum_required(VERSION 3.1.0)
project(graphics_lib VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
if(${CMAKE_BUILD_TYPE} MATCHES Debug)
    message("-- Debug Build")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -Ofast")
elseif(${CMAKE_BUILD_TYPE} MATCHES Release)
    message("-- Release Build")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()


set(CMAKE_BINARY_DIR "${CMAKE_SOURCE_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
set(LIBS glfw3 glew32 opengl32)


add_executable(${PROJECT_NAME} ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib/include ${CMAKE_SOURCE_DIR}/include)
target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib/lib)
target_link_libraries(${PROJECT_NAME} -static ${LIBS})

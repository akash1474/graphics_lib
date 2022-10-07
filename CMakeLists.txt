cmake_minimum_required(VERSION 3.1.0)
project(graphics_lib VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -mwindows")


set(CMAKE_BINARY_DIR "${CMAKE_SOURCE_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
# find_package(OpenGL REQUIRED)


# add_subdirectory(bin)
file(GLOB_RECURSE SRC_FILES src/*.cpp)
set(CMAKE_BUILD_TYPE static)
# set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_EXE_LINKER_FLAGS "-static")


set(LIBS glfw3 glew32 opengl32)
# include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/lib/include)
# link_directories(${CMAKE_SOURCE_DIR}/lib/mingw)
# link_libraries(-static ${LIBS})

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/lib/include ${CMAKE_SOURCE_DIR}/include)
if(${CMAKE_BUILD_COMPILER} MATCHES mingw)
	message("-- Initlizing MINGW Build")
	target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/lib/lib/mingw)
elseif(${CMAKE_BUILD_COMPILER} MATCHES msvc)
	message("-- Initlizing MSVC Build")
	target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/lib/msvc)
endif()

target_link_libraries(${PROJECT_NAME} -static ${LIBS})


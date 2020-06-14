cmake_minimum_required(VERSION 3.10)

project(cub3d C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS "-Wextra -Wall -Werror")

set(HALIDE_DISTRIB_USE_STATIC_LIBRARY TRUE)

include_directories(includes)
include_directories(libft/includes)
if (APPLE)
    include_directories(mlx/osx)
endif (APPLE)
if (LINUX)
    include_directories(mlx/linux)
endif(LINUX)

file(GLOB SRCS "srcs/*.c")
#file(GLOB LIBFT "libft/*.c")
if (LINUX)
    link_libraries(X11)
    link_libraries(m)
    link_libraries(Xext)
endif(LINUX)

add_executable(cub3d ${SRCS})

#target_link_libraries(cub3d ${PROJECT_LINK_LIBFT})
target_link_libraries(cub3d ${CMAKE_SOURCE_DIR}/libft/libftprintf.a)
if (APPLE)
    target_link_libraries(cub3d ${CMAKE_SOURCE_DIR}/mlx/osx/libmlx.dylib)
    target_link_libraries(cub3d "-framework OpenGL -framework AppKit")
endif (APPLE)
if (LINUX)
    target_link_libraries(cub3d ${CMAKE_SOURCE_DIR}/mlx/linux/libmlx.a)
endif(LINUX)
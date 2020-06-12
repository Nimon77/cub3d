cmake_minimum_required(VERSION 3.10)

project(cub3d C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS "-Wextra -Wall -Werror")

set(HALIDE_DISTRIB_USE_STATIC_LIBRARY TRUE)

include_directories(includes)
include_directories(libft)

file(GLOB SRCS "srcs/*.c")
#file(GLOB LIBFT "libft/*.c")
link_libraries(mlx)
link_libraries(X11)
link_libraries(m)
link_libraries(Xext)
#file(GLOB MLX "mlx/libmlx.a")
#file(GLOB MLX "./mlx/libmlx.dylib")

add_executable(cub3d ${SRCS})

#target_link_libraries(cub3d ${PROJECT_LINK_LIBFT})
target_link_libraries(cub3d ${CMAKE_SOURCE_DIR}/libft/libft.a)
if (APPLE)
    target_link_libraries(cub3d ${CMAKE_SOURCE_DIR}/mlx/libmlx.dylib)
    target_link_libraries(cub3d "-framework OpenGL -framework AppKit")
endif (APPLE)

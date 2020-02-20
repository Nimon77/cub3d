cmake_minimum_required(VERSION 3.10)

project(cub3d C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS "-Wextra -Wall -Werror")

set(PROJECT_LINK_MLX libmlx.dylib)
link_directories(mlx)
set(PROJECT_LINK_LIBFT libft.a)
link_directories(libft)

include_directories(includes)

file(GLOB SRCS "srcs/*.c")

add_executable(cub3d ${SRCS})

target_link_libraries(cub3d ${PROJECT_LINK_LIBFT})
target_link_libraries(cub3d ${PROJECT_LINK_MLX})
target_link_libraries(cub3d "-framework OpenGL -framework AppKit")

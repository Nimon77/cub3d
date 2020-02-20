#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../mlx/mlx.h"

typedef struct    data_s
{
	void          *mlx_ptr;
	void          *mlx_win;
}                 data_t;

int main(void)
{
	int 	width;
	int 	height;
	void	*image;
	data_t	data;
	
	width = 640;
	height = 480;
	if ((data.mlx_ptr = mlx_init()) == NULL)
		return (EXIT_FAILURE);
	if ((data.mlx_win = mlx_new_window(data.mlx_ptr, width, height, "Hello world"))
	== NULL)
		return (EXIT_FAILURE);
	image = mlx_png_file_to_image(data.mlx_ptr, "Test.png", &width, &height);
	mlx_put_image_to_window(data.mlx_ptr, data.mlx_win, image, 0, 0);
	mlx_loop(data.mlx_ptr);
	return (EXIT_SUCCESS);
}
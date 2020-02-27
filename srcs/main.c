/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 11:21:10 by nsimon            #+#    #+#             */
/*   Updated: 2020/02/27 15:56:50 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <fcntl.h>

#include "libft.h"
#include "cub3d.h"

/**
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../mlx/mlx.h"

typedef struct	data_s
{
	int 		size[2];
	void		*mlx_ptr;
	void		*mlx_win;
}				data_t;

void	put_color(int color, data_t *data)
{
	int i;
	int j;
	
	i = 0;
	while (i < data->size[0])
	{
		j = 0;
		while (j < data->size[1])
			mlx_pixel_put(data->mlx_ptr, data->mlx_win, i, j++, color);
		i++;
	}
}

int main(void)
{
	int 	width;
	int 	height;
	void	*image;
	data_t	data;
	
	width = 640;
	height = 480;
	data.size[0] = width;
	data.size[1] = height;
	if ((data.mlx_ptr = mlx_init()) == NULL)
		return (EXIT_FAILURE);
	if ((data.mlx_win = mlx_new_window(data.mlx_ptr, width, height, "Hello world"))
	== NULL)
		return (EXIT_FAILURE);
	image = mlx_png_file_to_image(data.mlx_ptr, "images/test.png", &width,
			&height);
	put_color(0x008080, &data);
	mlx_put_image_to_window(data.mlx_ptr, data.mlx_win, image, 0, 0);
	mlx_loop(data.mlx_ptr);
	return (EXIT_SUCCESS);
}**/

int	init(cub_t *cub)
{
	if ((cub->m_ptr = mlx_init()) == NULL)
		return (EXIT_FAILURE);
	cub->width = 0;
	cub->height = 0;
	cub->map = malloc(sizeof(*cub->map));
	cub->map[0] = ft_strdup("");
	cub->p_x = -1;
	cub->p_y = -1;
	cub->hit = 0;
	return (0);
}

void aff_map(char **map)
{
	int		i;
	
	i = 0;
	while (map[i][0] != '\0')
		printf("%s\n", map[i++]);
}

void	put_color(int color, cub_t *cub)
{
	int i;
	int j;
	
	i = 0;
	while (i < cub->width)
	{
		j = 0;
		while (j < cub->height)
			mlx_pixel_put(cub->m_ptr, cub->m_win, i, j++, color);
		i++;
	}
}

int	main(int argc, char **argv)
{
	cub_t cub;
	
	if (argc > 1)
	{
		if (init(&cub) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		ft_parse(&cub, argv[1]);
		//aff_map(cub.map);
		cub.m_win = mlx_new_window(cub.m_ptr, cub.width, cub.height, "cub3d");
		//put_color(cub.sol, &cub);
		mlx_key_hook(cub.m_win, &ft_move, &cub);
		//mlx_loop_hook(cub.m_ptr, &raycast, &cub);
		mlx_loop(cub.m_ptr);
	}
	
}

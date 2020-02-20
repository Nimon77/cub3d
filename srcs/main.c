/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 11:21:10 by nsimon            #+#    #+#             */
/*   Updated: 2020/02/20 12:05:08 by nsimon           ###   ########.fr       */
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
	image = mlx_png_file_to_image(data.mlx_ptr, "images/test.png", &width,
			&height);
	mlx_put_image_to_window(data.mlx_ptr, data.mlx_win, image, 0, 0);
	mlx_loop_hook(data.mlx_ptr, );
	return (EXIT_SUCCESS);
}
**/

void	get_size(char *str, cub_t *cub)
{
	int	i;
	int j;
	
	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]))
		{
			cub->height = ft_atoi(&str[i++]);
			while (!ft_isdigit(str[i - 1]) && ft_isdigit(str[i]))
				i++;
			cub->width = ft_atoi(&str[i]);
		}
		i++;
	}
}

void	ft_parser(char *str, cub_t *cub)
{
	str[0] == 'R' ? get_size(str, cub) : 0;
}

int	main(int argc, char **argv)
{
	int		fd;
	char	*str;
	cub_t	cub;
	
	if (argc > 1)
	{
		fd = open(argv[1], O_RDONLY);
		while (get_next_line(fd, &str) > 0)
		{
			ft_parser(str, &cub);
			printf("%s\n", str);
			free(str);
		}
		close(fd);
	}
	
}
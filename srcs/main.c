/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 11:21:10 by nsimon            #+#    #+#             */
/*   Updated: 2020/02/21 21:07:44 by nsimon           ###   ########.fr       */
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
	cub->map = NULL;
	return (0);
}

void aff_map(t_list *map)
{
	t_list *current;
	
	current = map;
	while (current != NULL)
	{
		printf("%s\n", current->content);
		current = current->next;
	}
}

int	main(int argc, char **argv)
{
	int   fd;
	char  *str;
	cub_t cub;
	
	if (argc > 1)
	{
		if (init(&cub) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		fd = open(argv[1], O_RDONLY);
		while (get_next_line(fd, &str) > 0)
		{
			ft_parse(str, &cub);
			free(str);
		}
		aff_map(cub.map);
		printf("%d", ft_lstsize(cub.map));
		close(fd);
	}
	
}

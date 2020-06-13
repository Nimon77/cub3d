/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 18:20:27 by nsimon            #+#    #+#             */
/*   Updated: 2020/06/13 18:26:28 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		get_sprite(char **map, t_cub *cub)
{
	int i;
	int j;

	i = 0;
	cub->nbrsprt = 0;
	while (map[i][0])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] > '1')
				cub->nbrsprt++;
			j++;
		}
		i++;
	}
}

void		get_pose(char **map, t_cub *cub)
{
	int x;
	int y;

	x = 0;
	while (map[x][0] != 0)
	{
		y = 0;
		while (map[x][y])
		{
			if (ft_isalpha(map[x][y]) && cub->pos.x != -1 && cub->pos.y != -1)
				ft_error(6);
			if ((map[x][y] == 'N' || map[x][y] == 'E' || map[x][y] == 'S' ||
				map[x][y] == 'W') && cub->pos.x == -1 && cub->pos.y == -1)
			{
				cub->pos.x = x + 0.5;
				cub->pos.y = y + 0.5;
				calc_dir(cub, map[x][y]);
				cub->map[x][y] = '0';
			}
			y++;
		}
		x++;
	}
}

int			get_color(char *str)
{
	int		i;
	t_color	rvb;

	i = 2;
	while (str[i] == ' ' && str[i])
		i++;
	check_color(str, &rvb);
	while (str[i])
	{
		if (ft_isdigit(str[i]) && str[i - 1] != ',' && rvb.r == -1 &&
			!ft_isdigit(str[i - 1]))
			rvb.r = ft_atoi(&str[i]);
		else if (ft_isdigit(str[i]) && str[i - 1] == ',' && rvb.v == -1 &&
				rvb.r != -1)
			rvb.r > -1 ? rvb.v = ft_atoi(&str[i]) : 0;
		else if (ft_isdigit(str[i]) && str[i - 1] == ',' && rvb.b == -1 &&
				rvb.r != -1 && rvb.v != -1)
			rvb.r > -1 && rvb.v > -1 ? rvb.b = ft_atoi(&str[i]) : 0;
		i++;
	}
	if (rvb.r < 0 || rvb.v < 0 || rvb.b < 0 || rvb.r > 255 || rvb.v > 255 ||
		rvb.b > 255)
		return (-1);
	return ((rvb.r * 256 * 256) + (rvb.v * 256) + (rvb.b));
}

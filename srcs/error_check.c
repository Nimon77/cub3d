/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 18:07:42 by nsimon            #+#    #+#             */
/*   Updated: 2020/06/15 18:19:16 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				check_textures(char *str)
{
	int	i;
	int	j;
	int	fd;

	i = 0;
	while (str[i] != ' ' || str[i + 1] == ' ')
		i++;
	j = i + 1;
	while (str[i])
		i++;
	while (i > 2)
	{
		if (str[i] == '.')
			if (str[i++] == '.')
			{
				str[i++] != 'x' ? ft_error(8) : 0;
				str[i++] != 'p' ? ft_error(8) : 0;
				str[i] != 'm' ? ft_error(8) : 0;
				break ;
			}
		i--;
	}
	((fd = open(&str[j], O_RDONLY)) == -1) ? ft_error(10) : 0;
	close(fd);
	return (0);
}

void			ft_error(int error)
{
	error == 1 ? ft_printf("Error\nResolution\n") : 0;
	error == 2 ? ft_printf("Error\nTextures\n") : 0;
	error == 3 ? ft_printf("Error\nSprite\n") : 0;
	error == 4 ? ft_printf("Error\nColor of ground\n") : 0;
	error == 5 ? ft_printf("Error\nColor of sky\n") : 0;
	error == 6 ? ft_printf("Error\nMap\n") : 0;
	error == 7 ? ft_printf("Error\nStart position\n") : 0;
	error == 8 ? ft_printf("Error\nTexture not XPM format\n") : 0;
	error == 9 ? ft_printf("Error\nSprite not XPM format\n") : 0;
	error == 10 ? ft_printf("Error\nOpen textures\n") : 0;
	error == 11 ? ft_printf("Error\nMultiple textures for side or sprite\n")
				: 0;
	error == 12 ? ft_printf("Error\nError color of floor or sky\n") : 0;
	error == 13 ? ft_printf("Error\nMultiple resolution\n") : 0;
	error == 14 ? ft_printf("Error\nmlx_init impossible\n") : 0;
	error == 15 ? ft_printf("Error\n.cub file not found or corrupted\n") : 0;
	error == 96 ? ft_printf("Error\nMap is not .cub format\n") : 0;
	error == 97 ? ft_printf("Usage : ./Cub3D map.cub\nOption : --save\n") : 0;
	error == 98 ? ft_printf("Error\nUsage : ./Cub3D map.cub\nOption : --save\n")
				: 0;
	error == 99 ? ft_printf("Error\nMalloc\n") : 0;
	exit(0);
}

void			check_parse_error(t_cub *cub)
{
	int	map_error;

	cub->win.w <= 0 || cub->win.h <= 0 ? ft_error(1) : 0;
	!cub->no || !cub->so || !cub->ea || !cub->we ? ft_error(2) : 0;
	!cub->no->img || !cub->ea->img || !cub->so->img || !cub->we->img ?
		ft_error(2) : 0;
	!cub->sprite ? ft_error(3) : 0;
	!cub->sprite->img ? ft_error(3) : 0;
	cub->sol == -1 ? ft_error(4) : 0;
	cub->plafond == -1 ? ft_error(5) : 0;
	map_error = check_map(cub);
	map_error ? ft_free_matrice(cub->map) : 0;
	map_error ? ft_error(6) : 0;
	cub->pos.x == -1 || cub->pos.y == -1 ? ft_error(7) : 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 18:14:21 by nsimon            #+#    #+#             */
/*   Updated: 2020/06/13 18:19:10 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		verif_size(char *str)
{
	int	i;

	i = 2;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]) && str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

void	check_color(char *str, t_color *rvb)
{
	int	i;

	i = 2;
	rvb->r = -1;
	rvb->v = -1;
	rvb->b = -1;
	while (str[i] == ' ' && str[i])
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != ',')
			ft_error(12);
		i++;
	}
}

void	ft_free_matrice(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i][0] != '\0')
			free(str[i++]);
		free(str[i]);
		free(str);
	}
}

void	calc_dir(t_cub *cub, char c)
{
	cub->dir.x = 0;
	cub->dir.y = 0;
	cub->plane.x = 0;
	cub->plane.y = 0;
	if (c == 'N')
	{
		cub->dir.x = -1;
		cub->plane.y = 0.66;
	}
	else if (c == 'S')
	{
		cub->dir.x = 1;
		cub->plane.y = -0.66;
	}
	else if (c == 'W')
	{
		cub->dir.y = -1;
		cub->plane.x = -0.66;
	}
	else if (c == 'E')
	{
		cub->dir.y = 1;
		cub->plane.x = 0.66;
	}
}

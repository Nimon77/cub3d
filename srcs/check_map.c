/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 17:22:22 by nsimon            #+#    #+#             */
/*   Updated: 2020/06/13 17:27:49 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		ft_ismap(char c)
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W' || c == '1' || c == '0' ||
		c == '2')
		return (1);
	return (0);
}

int				check_square(char **map, int i, int j)
{
	if (!ft_ismap(map[i - 1][j - 1]) || !ft_ismap(map[i - 1][j])
			|| !ft_ismap(map[i - 1][j + 1]) || !ft_ismap(map[i][j + 1])
			|| !ft_ismap(map[i + 1][j + 1]) || !ft_ismap(map[i + 1][j]) ||
			!ft_ismap(map[i + 1][j - 1]) || !ft_ismap(map[i][j - 1]))
		return (1);
	return (0);
}

int				check_map(t_cub *cub)
{
	int		i;
	int		j;
	char	**map;

	map = cub->map;
	i = 0;
	while (map[i][0] != '\0')
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S' ||
				map[i][j] == 'E' || map[i][j] == 'W' || map[i][j] == '2')
			{
				if (i == 0 || map[i + 1][0] == 0 || j == 0 ||
					map[i][j + 1] == 0)
					return (1);
				if (check_square(map, i, j))
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

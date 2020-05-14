/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 18:07:42 by nsimon            #+#    #+#             */
/*   Updated: 2020/04/28 18:28:23 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		ft_ismap(char c)
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W' || ft_isdigit(c))
		return (1);
	return (0);
}

void 	check_map(t_cub *cub)
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
					map[i][j] == 'E' || map[i][j] == 'W')
			{
				if (i == 0 || map[i + 1][0] == 0 || j == 0 ||
						map[i][j + 1] == 0)
					ft_error(3);
				if (!ft_ismap(map[i - 1][j - 1]) || !ft_ismap(map[i - 1][j])
						|| !ft_ismap(map[i - 1][j + 1]) ||
						!ft_ismap(map[i][j + 1]) || !ft_ismap(map[i + 1][j + 1])
						|| !ft_ismap(map[i + 1][j]) ||
						!ft_ismap(map[i + 1][j - 1])|| !ft_ismap(map[i][j - 1]))
					ft_error(3);
			}
			j++;
		}
		i++;
	}
}

void	ft_error(int error)
{
	exit(error);
}
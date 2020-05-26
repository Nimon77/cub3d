/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 20:11:35 by nsimon            #+#    #+#             */
/*   Updated: 2020/05/26 15:49:56 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_size(char *str, t_cub *cub)
{
	int	i;
	
	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]))
		{
			cub->win.w == 0 ? cub->win.w = ft_atoi(&str[i]) : 0;
			while (str[i] != ' ' && str[i] != '\0')
				i++;
			cub->win.h == 0 ? cub->win.h = ft_atoi(&str[i]) : 0;
		}
		else
			i++;
	}
}

t_texture	*get_texture(char *str, t_cub *cub)
{
	int	i;
	int j;
	int fd;
	t_texture *img;
	char pth[256];
	
	i = 2;
	j = 0;
	ft_memset(&pth, 0, 256);
	while (str[i] == ' ' && str[i])
		i++;
	while (str[i] != ' ' && str[i])
		pth[j++] = str[i++];
	if ((fd = open(pth, O_RDONLY)) == -1)
		return (NULL);
	close(fd);
	if ((img = malloc(sizeof(*img))) == NULL)
		return NULL;
//	img->img = mlx_png_file_to_image(cub->m_ptr, pth, &img->size.w,
//	 	&img->size.h);
	return (img);
}

void	ft_free_matrice(char **str)
{
	int		i;
	
	i = 0;
	while (str[i][0] != '\0')
		free(str[i++]);
	free(str[i]);
	free(str);
}

void	get_map(char *str, t_cub *cub)
{
	int 	i[2];
	char	**tmp;
	
	i[0] = -1;
	i[1] = 0;
	while (cub->map[i[1]][0] != '\0')
		i[1]++;
	tmp = malloc(sizeof(*tmp) * (i[1] + 2));
	while (++i[0] < i[1])
		tmp[i[0]] = ft_strdup(cub->map[i[0]]);
	ft_free_matrice(cub->map);
	tmp[i[0]] == NULL ? free(tmp[i[0]]) : 0;
	tmp[i[0]++] = ft_strdup(str);
	tmp[i[0]] = ft_strdup("");
	cub->map = tmp;
}

int		get_color(char *str)
{
	int		i;
	t_color	rvb;
	
	i = 2;
	while (str[i] == ' ' && str[i])
		i++;
	rvb.r = -1;
	rvb.v = -1;
	rvb.b = -1;
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

int		check_error(t_cub *cub)
{
	if (cub->no == NULL || cub->ea == NULL || cub->so == NULL ||
			cub->we == NULL || cub->sprite == NULL || cub->map == NULL)
		ft_error(1);
	if (cub->sol == -1 || cub->plafond == -1)
		ft_error(2);
	check_map(cub);
	return (0);
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

void	get_pose(char **map, t_cub *cub)
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
				ft_error(3);
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

void 	ft_select(char *str, t_cub *cub)
{
	str[0] == 'R' ? get_size(str, cub) : 0;
	str[0] == 'N' && str[1] == 'O' ? cub->no = get_texture(str, cub) : 0;
	str[0] == 'S' && str[1] == 'O' ? cub->so = get_texture(str, cub) : 0;
	str[0] == 'W' && str[1] == 'E' ? cub->we = get_texture(str, cub) : 0;
	str[0] == 'E' && str[1] == 'A' ? cub->ea = get_texture(str, cub) : 0;
	str[0] == 'S' && str[1] == ' ' ? cub->sprite = get_texture(str, cub) : 0;
	str[0] == 'F' ? cub->sol = get_color(str) : 0;
	str[0] == 'C' ? cub->plafond = get_color(str) : 0;
	ft_isdigit(str[0]) || str[0] == ' ' ? get_map(str, cub) : 0;
}

void	ft_parse(t_cub *cub, char *path)
{
	int		fd;
	char	*str;
	
	fd = open(path, O_RDONLY);
	while (get_next_line(fd, &str) > 0)
	{
		ft_select(str, cub);
		free(str);
	}
	ft_select(str, cub);
	free(str);
	check_error(cub);
	get_pose(cub->map, cub);
	close(fd);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 20:11:35 by nsimon            #+#    #+#             */
/*   Updated: 2020/06/13 03:38:10 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			verif_size(char *str)
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

void		get_size(char *str, t_cub *cub)
{
	int	i;
	int size[2];
	
	i = 2;
	if (verif_size(str))
		return;
	if (ft_isdigit(str[i]))
	{
		cub->win.w == 0 ? cub->win.w = ft_atoi(&str[i]) : 0;
		while (str[i] != ' ' && str[i] != '\0')
			i++;
		cub->win.h == 0 ? cub->win.h = ft_atoi(&str[i]) : 0;
	}
	mlx_get_screen_size(cub->m_ptr, &size[1], &size[0]);
	cub->win.h > size[0] - 45 ? cub->win.h = size[0] - 45 : 0;
	cub->win.w > size[1] ? cub->win.w = size[1] : 0;
}

t_texture 	*get_texture(char *str, t_cub *cub, t_texture *tex)
{
	int	i;
	int j;
	t_texture *img;
	char pth[256];

	tex != NULL ? ft_error(11) : 0;
	i = 2;
	j = check_textures(str);
	ft_memset(&pth, 0, 256);
	while (str[i] == ' ' && str[i])
		i++;
	while (str[i] != ' ' && str[i])
		pth[j++] = str[i++];
	if ((img = malloc(sizeof(*img))) == NULL)
		ft_error(99);
	img->img = mlx_xpm_file_to_image(cub->m_ptr, pth, &img->size.w,
			&img->size.h);
	img->addr = (int *)mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	return (img);
}

void		ft_free_matrice(char **str)
{
	int		i;
	
	i = 0;
	if (str)
	{
		while (str[i][0] != '\0')
			free(str[i++]);
		free(str[i]);
		free(str);
	}
}

void		get_map(char *str, t_cub *cub)
{
	int 	i[2];
	char	**tmp;
	
	i[0] = -1;
	i[1] = 0;
	while (cub->map[i[1]][0] != '\0')
		i[1]++;
	if ((tmp = malloc(sizeof(*tmp) * (i[1] + 2))) == NULL)
		ft_error(99);
	while (++i[0] < i[1])
		tmp[i[0]] = ft_strdup(cub->map[i[0]]);
	ft_free_matrice(cub->map);
	tmp[i[0]] == NULL ? free(tmp[i[0]]) : 0;
	tmp[i[0]++] = ft_strdup(str);
	tmp[i[0]] = ft_strdup("");
	cub->map = tmp;
}

void check_color(char *str, t_color *rvb)
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

void		calc_dir(t_cub *cub, char c)
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

void 		ft_select(char *str, t_cub *cub)
{
	str[0] == 'R' ? get_size(str, cub) : 0;
	if (str[0] == 'N' && str[1] == 'O')
		cub->no = get_texture(str, cub, cub->no);
	if (str[0] == 'S' && str[1] == 'O')
		cub->so = get_texture(str, cub, cub->so);
	if (str[0] == 'W' && str[1] == 'E')
		cub->we = get_texture(str, cub, cub->we);
	if (str[0] == 'E' && str[1] == 'A')
		cub->ea = get_texture(str, cub, cub->ea);
	if (str[0] == 'S' && str[1] == ' ')
		cub->sprite = get_texture(str, cub, cub->sprite);
	str[0] == 'F' ? cub->sol = get_color(str) : 0;
	str[0] == 'C' ? cub->plafond = get_color(str) : 0;
	ft_isdigit(str[0]) || str[0] == ' ' ? get_map(str, cub) : 0;
}

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

void		ft_parse(t_cub *cub, char *path)
{
	int		fd;
	char	*str;
	
	fd = open(path, O_RDONLY);
	while (get_next_line(fd, &str) > 0)
	{
		if (cub->map[0][0] != '\0' && str[0] == '\0')
			break;
		ft_select(str, cub);
		free(str);
	}
	if (str[0] != '\0' && cub->map[0][0] == '\0')
		ft_select(str, cub);
	free(str);
	get_pose(cub->map, cub);
	get_sprite(cub->map, cub);
	close(fd);
}
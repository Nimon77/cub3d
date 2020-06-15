/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 20:11:35 by nsimon            #+#    #+#             */
/*   Updated: 2020/06/15 18:29:00 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		get_size(char *str, t_cub *cub)
{
	int	i;
	int size[2];

	i = 2;
	if (cub->win.h != 0 && cub->win.w != 0)
		ft_error(13);
	if (verif_size(str))
		return ;
	while (!ft_isdigit(str[i]))
		i++;
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

t_texture	*get_texture(char *str, t_cub *cub, t_texture *tex)
{
	int			i;
	int			j;
	t_texture	*img;
	char		pth[257];

	tex != NULL ? ft_error(11) : 0;
	i = 2;
	j = check_textures(str);
	ft_memset(&pth, 0, 257);
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

void		get_map(char *str, t_cub *cub)
{
	int		i[2];
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

static void	ft_select(char *str, t_cub *cub)
{
	int i;

	i = 0;
	str[0] == 'R' && str[1] == ' ' ? get_size(str, cub) : 0;
	if (str[0] == 'N' && str[1] == 'O' && str[2] == ' ')
		cub->no = get_texture(str, cub, cub->no);
	if (str[0] == 'S' && str[1] == 'O' && str[2] == ' ')
		cub->so = get_texture(str, cub, cub->so);
	if (str[0] == 'W' && str[1] == 'E' && str[2] == ' ')
		cub->we = get_texture(str, cub, cub->we);
	if (str[0] == 'E' && str[1] == 'A' && str[2] == ' ')
		cub->ea = get_texture(str, cub, cub->ea);
	if (str[0] == 'S' && str[1] == ' ')
		cub->sprite = get_texture(str, cub, cub->sprite);
	str[0] == 'F' && str[1] == ' ' ? cub->sol = get_color(str) : 0;
	str[0] == 'C' && str[1] == ' ' ? cub->plafond = get_color(str) : 0;
	while (str[i++] == ' ')
		ft_isdigit(str[i]) ? get_map(str, cub) : 0;
	ft_isdigit(str[0]) ? get_map(str, cub) : 0;
}

void		ft_parse(t_cub *cub, char *path)
{
	int		fd;
	char	*str;

	if ((fd = open(path, O_RDONLY)) < 0)
		ft_error(15);
	while (get_next_line(fd, &str) > 0)
	{
		if (cub->map[0][0] != '\0' && str[0] == '\0')
			break ;
		ft_select(str, cub);
		free(str);
	}
	ft_select(str, cub);
	free(str);
	get_pose(cub->map, cub);
	get_sprite(cub->map, cub);
	close(fd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 20:11:35 by nsimon            #+#    #+#             */
/*   Updated: 2020/02/24 20:17:07 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_size(char *str, cub_t *cub)
{
	int	i;
	
	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]))
		{
			cub->width == 0 ? cub->width = ft_atoi(&str[i]) : 0;
			while (str[i] != ' ' && str[i] != '\0')
				i++;
			cub->height == 0 ? cub->height = ft_atoi(&str[i]) : 0;
		}
		else
			i++;
	}
}

image_t	*get_texture(char *str, cub_t *cub)
{
	int	i;
	int j;
	image_t *img;
	char pth[256];
	
	i = 2;
	j = 0;
	ft_memset(&pth, 0, 256);
	while (str[i] == ' ' && str[i])
		i++;
	while (str[i] != ' ' && str[i])
		pth[j++] = str[i++];
	img = malloc(sizeof(*img));
	img->img = mlx_png_file_to_image(cub->m_ptr, pth, &img->wdt, &img->height);
	return (img);
}

void	ft_free_matrice(char **str)
{
	int		i;
	
	i = 0;
	while (str[i][0] != '\0')
		free(str[i++]);
	free(str);
}

void	get_map(char *str, cub_t *cub)
{
	int 	i[4];
	char	**tmp;
	char 	line[512];
	
	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	i[3] = 0;
	while (cub->map[i[3]][0] != '\0')
		i[3]++;
	tmp = malloc(sizeof(*tmp) * (i[3] + 2));
	while (i[0] < i[3])
		tmp[i[0]] = ft_strdup(cub->map[i[0]++]);
	ft_free_matrice(cub->map);
	tmp[i[0]] == NULL ? free(tmp[i[0]]) : 0;
	while (str[i[1]] != '\0')
		str[i[1]] != ' ' ? line[i[2]++] = str[i[1]++] : i[1]++;
	tmp[i[0]++] = ft_strdup(line);
	tmp[i[0]] = ft_strdup("");
	cub->map = tmp;
}

int		get_color(char *str)
{
	int		i;
	color_t	rvb;
	
	i = 2;
	while (str[i] == ' ' && str[i])
		i++;
	rvb.R = -1;
	rvb.V = -1;
	rvb.B = -1;
	while (str[i])
	{
		if (ft_isdigit(str[i]) && str[i - 1] != ',' && rvb.R == -1)
			rvb.R = ft_atoi(&str[i]);
		else if (ft_isdigit(str[i]) && str[i - 1] == ',' && rvb.V == -1)
			rvb.R > -1 ? rvb.V = ft_atoi(&str[i]) : 0;
		else if (ft_isdigit(str[i]) && str[i - 1] == ',' && rvb.B == -1)
			rvb.R > -1 && rvb.V > -1 ? rvb.B = ft_atoi(&str[i]) : 0;
		i++;
	}
	if (rvb.R < 0 || rvb.V < 0 || rvb.B < 0 || rvb.R > 255 || rvb.V > 255 ||
	        rvb.B > 255)
		return (-1);
	return ((rvb.R * 256 * 256) + (rvb.V * 256) + (rvb.B));
}

int		check_error(cub_t *cub)
{
	if (cub->NO == NULL || cub->EA == NULL || cub->SO == NULL ||
			cub->WE == NULL || cub->sprite == NULL || cub->map == NULL)
		return (1);
	if (cub->sol == -1 || cub->plafond == -1)
		return (1);
	return (0);
}

int		ft_parse(char *str, cub_t *cub)
{
	str[0] == 'R' ? get_size(str, cub) : 0;
	str[0] == 'N' && str[1] == 'O' ? cub->NO = get_texture(str, cub) : 0;
	str[0] == 'S' && str[1] == 'O' ? cub->SO = get_texture(str, cub) : 0;
	str[0] == 'W' && str[1] == 'E' ? cub->WE = get_texture(str, cub) : 0;
	str[0] == 'E' && str[1] == 'A' ? cub->EA = get_texture(str, cub) : 0;
	str[0] == 'S' && str[1] == ' ' ? cub->sprite = get_texture(str, cub) : 0;
	str[0] == 'F' ? cub->sol = get_color(str) : 0;
	str[0] == 'C' ? cub->plafond = get_color(str) : 0;
	str[0] == '1' ? get_map(str, cub) : 0;
	return (check_error(cub));
}
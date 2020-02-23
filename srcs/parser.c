/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 20:11:35 by nsimon            #+#    #+#             */
/*   Updated: 2020/02/23 11:27:39 by nsimon           ###   ########.fr       */
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
			cub->width == 0 ? cub->width = ft_atoi(&str[i++]) : 0;
			while (str[i] != ' ')
				i++;
			cub->height == 0 ? cub->height = ft_atoi(&str[i]) : 0;
		}
		i++;
	}
}


void	*get_texture(char *str, cub_t *cub)
{
	int	i;
	int j;
	char pth[256];
	
	i = 2;
	j = 0;
	ft_memset(&pth, 0, 256);
	while (str[i] == ' ' && str[i])
		i++;
	while (str[i] != ' ' && str[i])
		pth[j++] = str[i++];
	return (mlx_png_file_to_image(cub->m_ptr, pth, &cub->width, &cub->height));
}

void	get_map(char *str, cub_t *cub)
{
	int		i;
	int		j;
	char	*line;
	
	i = 0;
	j = 0;
	line = malloc(sizeof(*line) * (ft_strlen(str) + 1));
	ft_memset(line, 0, ft_strlen(str) + 1);
	while (str[i])
		str[i] != ' ' ? line[j++] = str[i++] : i++;
	line[j] = 0;
	ft_lstadd_back(&cub->map, ft_lstnew(ft_strdup(line)));
	free(line);
}

char 	*convert_hexa(char *str)
{
	int 	value;
	
	value = ft_atoi(str);
	if (value == 0)
		return (ft_strdup("00"));
	else
		return (ft_itoa_base(value, "0123456789ABCDEF"));
}

int		get_color(char *str)
{
	int		i;
	int		j;
	int		value;
	char	*col[2];
	color_t	rvb;
	
	i = 2;
	while (str[i] == ' ' && str[i])
		i++;
	j = 0;
	while (ft_isdigit(str[i]) && j < 4)
		rvb.R[j++] = str[i++];
	i++;
	j = 0;
	while (ft_isdigit(str[i]) && j < 4)
		rvb.V[j++] = str[i++];
	i++;
	j = 0;
	while (ft_isdigit(str[i]) && j < 4)
		rvb.B[j++] = str[i++];
	col[0] = convert_hexa(rvb.R);
	col[1] = ft_strjoin(col[0], convert_hexa(rvb.V));
	free(col[0]);
	col[0] = ft_strjoin(col[1], convert_hexa(rvb.B));
	free(col[1]);
	value = ft_atoi_base(col[0], "0123456789ABCDEF");
	free(col[0]);
	return (value);
}

void	ft_parse(char *str, cub_t *cub)
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
}
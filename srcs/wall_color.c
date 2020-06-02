/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 18:16:45 by nsimon            #+#    #+#             */
/*   Updated: 2020/06/02 16:07:23 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		color_wall(t_index *m, int i, int x, int drawend)
{
	if (m->ray.raydiry >= 0 && m->ray.side == 1)
		while (i < drawend)
		{
			m->img.addr[i * m->img.line_length + x] = 16711680;
			i++;
		}
	else if (m->ray.raydiry < 0 && m->ray.side == 1)
		while (i < drawend)
		{
			m->img.addr[i * m->img.line_length + x] = 65280;
			i++;
		}
	else if (m->ray.raydirx >= 0 && m->ray.side == 0)
		while (i < drawend)
		{
			m->img.addr[i * m->img.line_length + x] = 255;
			i++;
		}
	else
		while (i < drawend)
		{
			m->img.addr[i * m->img.line_length + x] = 16776960;
			i++;
		}
	return (i);
}


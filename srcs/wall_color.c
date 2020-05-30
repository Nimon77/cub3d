/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 18:16:45 by nsimon            #+#    #+#             */
/*   Updated: 2020/05/30 23:16:33 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		color_wall(t_index *m, int i, int x, int j, int drawEnd)
{
	int	color;
	
	if (m->ray.side == 1)
	{
		if (m->ray.raydiry >= 0)
			while (i < drawEnd)
			{
				m->img.addr[i * (m->cub.win.w + j) + x] = 16711680;
				i++;
			}
		else
			while (i < drawEnd)
			{
				m->img.addr[i * (m->cub.win.w + j) + x] = 65280;
				i++;
			}
	}
	else
	{
		if (m->ray.raydirx >= 0)
			color = 255;
		else
			color = 16776960;
	}
	return (i);
}


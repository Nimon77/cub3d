/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 15:56:47 by nsimon            #+#    #+#             */
/*   Updated: 2020/06/02 18:16:55 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	textures_wall(t_index *m, int i, int x, int drawend)
{
	double	step;
	double	texpos;
	int		texy;
	
	/*
	 * East
	 */
	if (m->ray.raydiry >= 0 && m->ray.side == 1)
	{
		m->ray.texx = (int)(m->ray.wallx * (double)m->cub.ea->size.h);
		step = 1.0 * m->cub.ea->size.h / m->ray.lineheight;
		texpos = (i - m->cub.win.h / 2 + m->ray.lineheight / 2) * step;
		while (i < drawend)
		{
			texy = (int)texpos & (m->cub.ea->size.h - 1);
			texpos += step;
			m->img.addr[i * m->img.line_length + x] =
					m->cub.ea->addr[texy * m->cub.ea->size.h * 2 + m->ray.texx];
			i++;
		}
	}
	/*
	 * West
	 */
	else if (m->ray.raydiry < 0 && m->ray.side == 1)
	{
		m->ray.texx = (int)(m->ray.wallx * (double)m->cub.we->size.h);
		m->ray.texx = m->cub.we->size.w - m->ray.texx - 1;
		step = 1.0 * m->cub.we->size.h / m->ray.lineheight;
		texpos = (i - m->cub.win.h / 2 + m->ray.lineheight / 2) * step;
		while (i < drawend)
		{
			texy = (int)texpos & (m->cub.we->size.h - 1);
			texpos += step;
			m->img.addr[i * m->img.line_length + x] =
					m->cub.we->addr[texy * m->cub.we->size.h * 2 + m->ray.texx];
			i++;
		}
	}
	/*
	 * South
	 */
	else if (m->ray.raydirx >= 0 && m->ray.side == 0)
	{
		m->ray.texx = (int)(m->ray.wallx * m->cub.so->size.h);
		m->ray.texx = m->cub.so->size.w - m->ray.texx - 1;
		step = 1.0 * m->cub.so->size.h / m->ray.lineheight;
		texpos = (i - m->cub.win.h / 2 + m->ray.lineheight / 2) * step;
		while (i < drawend)
		{
			texy = (int)texpos & (m->cub.so->size.h - 1);
			texpos += step;
			m->img.addr[i * m->img.line_length + x] =
					m->cub.so->addr[texy * m->cub.so->size.h * 2 + m->ray.texx];
			i++;
		}
	}
	/*
	 * North
	 */
	else
	{
		m->ray.texx = (int)(m->ray.wallx * (double)m->cub.no->size.h);
		step = 1.0 * m->cub.no->size.h / m->ray.lineheight;
		texpos = (i - m->cub.win.h / 2 + m->ray.lineheight / 2) * step;
		while (i < drawend)
		{
			texy = (int)texpos & (m->cub.no->size.h - 1);
			texpos += step;
			m->img.addr[i * m->img.line_length + x] =
					m->cub.no->addr[texy * m->cub.no->size.h * 2 + m->ray.texx];
			i++;
		}
	}
	return (i);
}
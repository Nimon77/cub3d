/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 20:59:09 by nsimon            #+#    #+#             */
/*   Updated: 2020/05/26 15:04:07 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_raycast(t_index *m, int x)
{
	m->ray.camerax = 2 * x / (double)m->cub.win.w - 1;
	m->ray.raydirx = m->cub.dir.x + m->cub.plane.x * m->ray.camerax;
	m->ray.raydiry = m->cub.dir.y + m->cub.plane.y * m->ray.camerax;
	m->ray.mapx = (int)m->cub.pos.x;
	m->ray.mapy = (int)m->cub.pos.y;
	m->ray.deltadistx = ABS(1 / m->ray.raydirx);
	m->ray.deltadisty = ABS(1 / m->ray.raydiry);
	m->ray.hit = 0;
}

void	calc_step_dist(t_index *m)
{
	if (m->ray.raydirx < 0)
	{
		m->ray.stepx = -1;
		m->ray.sidedistx = (m->cub.pos.x - m->ray.mapx) * m->ray.deltadistx;
	}
	else
	{
		m->ray.stepx = 1;
		m->ray.sidedistx = (m->ray.mapx + 1.0 - m->cub.pos.x) *
						   m->ray.deltadistx;
	}
	if (m->ray.raydirx < 0)
	{
		m->ray.stepy = -1;
		m->ray.sidedisty = (m->cub.pos.y - m->ray.mapy) * m->ray.deltadisty;
	}
	else
	{
		m->ray.stepy = 1;
		m->ray.sidedisty = (m->ray.mapy + 1.0 - m->cub.pos.y) *
				m->ray.deltadisty;
	}
}

void	dda(t_index *m)
{
	while (m->ray.hit == 0)
	{
		if (m->ray.sidedistx < m->ray.sidedisty)
		{
			m->ray.sidedistx += m->ray.deltadistx;
			m->ray.mapx += m->ray.stepx;
			m->ray.side = 0;
		}
		else
		{
			m->ray.sidedisty += m->ray.deltadisty;
			m->ray.mapy += m->ray.stepy;
			m->ray.side = 1;
		}
		if (m->cub.map[m->ray.mapx][m->ray.mapy] != '0')
			m->ray.hit = 1;
	}
	if (m->ray.side == 0)
		m->ray.perpwalldist = (m->ray.mapx - m->cub.pos.x +
							   (1 - m->ray.stepx) / 2) / m->ray.raydirx;
	else
		m->ray.perpwalldist = (m->ray.mapy - m->cub.pos.y +
							   (1 - m->ray.stepy) / 2) / m->ray.raydirx;
}

int		line_size(t_index *m)
{
	int	color;
	
	m->ray.lineheight = (int)(m->cub.win.h / m->ray.perpwalldist);
	m->ray.drawstart = -m->ray.lineheight / 2 + m->cub.win.h / 2;
	if (m->ray.drawstart < 0)
		m->ray.drawstart = 0;
	m->ray.drawend = m->ray.lineheight / 2 + m->cub.win.h / 2;
	if (m->ray.drawend >= m->cub.win.h)
		m->ray.drawend = m->cub.win.h - 1;
	switch (m->cub.map[m->ray.mapx][m->ray.mapy])
	{
		case '1':
			color = 16711680;
			break; //red
		case '2':
			color = 65280;
			break; //green
		case '3':
			color = 255;
			break; //blue
		case '4':
			color = 16777215;
			break; //white
		default:
			color = 16776960;
			break; //yellow
	}
	if (m->ray.side == 1)
	{
		color = color / 2;
	}
	return (color);
}

void	write_img(t_index *m, int drawStart, int drawEnd, int x, int color)
{
	int i;
	
	i = 0;
	while (i < drawStart)
	{
		m->img.addr[i * m->cub.win.w + x] = m->cub.plafond;
		i++;
	}
	while (i < drawEnd)
	{
		m->img.addr[i * m->cub.win.w + x] = color;
		i++;
	}
	while (i < m->cub.win.h)
	{
		m->img.addr[i * m->cub.win.w + x] = m->cub.sol;
		i++;
	}
}

int 	raycast(t_index *m)
{
	int x;
	int	color;
	
	x = 0;
	while (x < m->cub.win.w)
	{
		init_raycast(m, x);
		calc_step_dist(m);
		dda(m);
		color = line_size(m);
		write_img(m, m->ray.drawstart, m->ray.drawend, x, color);
		x++;
	}
	return (0);
}

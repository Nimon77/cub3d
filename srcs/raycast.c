/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 20:59:09 by nsimon            #+#    #+#             */
/*   Updated: 2020/05/25 18:21:14 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	init_raycast(t_index *m, int x)
{
	m->ray.cameraX = 2 * x / (double)m->cub.win.w - 1;
	m->ray.rayDirX = m->cub.dir.x + m->cub.plane.x * m->ray.cameraX;
	m->ray.rayDirY = m->cub.dir.y + m->cub.plane.y * m->ray.cameraX;
	m->ray.mapX = (int)m->cub.pos.x;
	m->ray.mapY = (int)m->cub.pos.y;
	m->ray.deltaDistX = ABS(1 / m->ray.rayDirX);
	m->ray.deltaDistY = ABS(1 / m->ray.rayDirY);
	m->ray.hit = 0;
}

void	calc_step_dist(t_index *m)
{
	if (m->ray.rayDirX < 0)
	{
		m->ray.stepX = -1;
		m->ray.sideDistX = (m->cub.pos.x - m->ray.mapX) * m->ray.deltaDistX;
	}
	else
	{
		m->ray.stepX = 1;
		m->ray.sideDistX = (m->ray.mapX + 1.0 - m->cub.pos.x) *
						   m->ray.deltaDistX;
	}
	if (m->ray.rayDirY < 0)
	{
		m->ray.stepY = -1;
		m->ray.sideDistY = (m->cub.pos.y - m->ray.mapY) * m->ray.deltaDistY;
	}
	else
	{
		m->ray.stepY = 1;
		m->ray.sideDistY = (m->ray.mapY + 1.0 - m->cub.pos.y) *
				m->ray.deltaDistY;
	}
}

void	dda(t_index *m)
{
	while (m->ray.hit == 0)
	{
		if (m->ray.sideDistX < m->ray.sideDistY)
		{
			m->ray.sideDistX += m->ray.deltaDistX;
			m->ray.mapX += m->ray.stepX;
			m->ray.side = 0;
		}
		else
		{
			m->ray.sideDistY += m->ray.deltaDistY;
			m->ray.mapY += m->ray.stepY;
			m->ray.side = 1;
		}
		if (m->cub.map[m->ray.mapX][m->ray.mapY] != '0')
			m->ray.hit = 1;
	}
	if (m->ray.side == 0)
		m->ray.perpWallDist = (m->ray.mapX - m->cub.pos.x +
							   (1 - m->ray.stepX) / 2) / m->ray.rayDirX;
	else
		m->ray.perpWallDist = (m->ray.mapY - m->cub.pos.y +
							   (1 - m->ray.stepY) / 2) / m->ray.rayDirY;
}

int		line_size(t_index *m)
{
	int	color;
	
	m->ray.lineHeight = (int)(m->cub.win.h / m->ray.perpWallDist);
	m->ray.drawStart = -m->ray.lineHeight / 2 + m->cub.win.h / 2;
	if (m->ray.drawStart < 0)
		m->ray.drawStart = 0;
	m->ray.drawEnd = m->ray.lineHeight / 2 + m->cub.win.h / 2;
	if (m->ray.drawEnd >= m->cub.win.h)
		m->ray.drawEnd = m->cub.win.h - 1;
	switch (m->cub.map[m->ray.mapX][m->ray.mapY])
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

int 	raycast(t_index *m)
{
	//mlx_clear_window(m->cub.m_ptr, m->cub.m_win);
	int x;
	int	color;
	
	x = 0;
	while (x < m->cub.win.w)
	{
		init_raycast(m, x);
		calc_step_dist(m);
		dda(m);
		color = line_size(m);
		write_img(m, m->ray.drawStart, m->ray.drawEnd, x, color);
		x++;
	}
}

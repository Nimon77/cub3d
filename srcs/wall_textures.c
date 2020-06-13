/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 15:56:47 by nsimon            #+#    #+#             */
/*   Updated: 2020/06/13 18:02:44 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_current_tex(t_index *m)
{
	if (m->ray.raydiry >= 0 && m->ray.side == 1)
		m->ray.current = m->cub.we;
	else if (m->ray.raydiry < 0 && m->ray.side == 1)
		m->ray.current = m->cub.ea;
	else if (m->ray.raydirx >= 0 && m->ray.side == 0)
		m->ray.current = m->cub.no;
	else
		m->ray.current = m->cub.so;
}

void	calc_vars(t_index *m, int i)
{
	if (m->ray.side == 0)
		m->ray.wallx = m->cub.pos.y + m->ray.perpwalldist * m->ray.raydiry;
	else
		m->ray.wallx = m->cub.pos.x + m->ray.perpwalldist * m->ray.raydirx;
	m->ray.wallx -= floor(m->ray.wallx);
	m->ray.texx = (int)(m->ray.wallx * (double)m->ray.current->size.h);
	if ((m->ray.side == 0 && m->ray.raydirx > 0) ||
		(m->ray.side == 1 && m->ray.raydiry < 0))
		m->ray.texx = m->ray.current->size.w - m->ray.texx - 1;
	m->ray.step = 1.0 * m->ray.current->size.h / m->ray.lineheight;
	m->ray.texpos = (i - m->cub.win.h / 2 + m->ray.lineheight / 2) *
			m->ray.step;
}

int		textures_wall(t_index *m, int i, int x, int drawend)
{
	int	texy;
	int color;

	find_current_tex(m);
	calc_vars(m, i);
	while (i < drawend)
	{
		texy = (int)m->ray.texpos & (m->ray.current->size.h - 1);
		m->ray.texpos += m->ray.step;
		if (m->ray.current->size.h < 64 && APPLE)
			color = m->ray.current->addr[texy * (m->ray.current->size.h * 64 /
								m->ray.current->size.h) + m->ray.texx];
		else
			color = m->ray.current->addr[texy * m->ray.current->size.h +
								m->ray.texx];
		if ((color & 0x00FFFFFF) == 0)
			color = 0;
		m->img.addr[i * m->img.line_length + x] = color;
		i++;
	}
	return (i);
}

void	write_img(t_index *m, int drawstart, int drawend, int x)
{
	int i;

	i = 0;
	while (i < drawstart)
	{
		m->img.addr[i * m->img.line_length + x] = m->cub.plafond;
		i++;
	}
	i = textures_wall(m, i, x, drawend);
	while (i < m->cub.win.h)
	{
		m->img.addr[i * m->img.line_length + x] = m->cub.sol;
		i++;
	}
}

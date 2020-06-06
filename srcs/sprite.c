/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 17:37:15 by nsimon            #+#    #+#             */
/*   Updated: 2020/06/06 19:33:00 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	index_sprite(t_index *m)
{
	int	count;
	int i;
	int j;
	
	i = 0;
	count = 0;
	while (m->cub.map[i][0])
	{
		j = 0;
		while (m->cub.map[i][j])
		{
			if (m->cub.map[i][j] > '1')
			{
				m->sprite[count].x = i;
				m->sprite[count].y = j;
				count++;
			}
			j++;
		}
		i++;
	}
}

void	sort_sprite(t_index *m)
{
	int			i;
	int 		j;
	int			d;
	t_sprite	tmp;
	
	
	i = 0;
	while (i < m->cub.nbrsprt)
	{
		j = i + 1;
		while (j < m->cub.nbrsprt)
		{
			if (m->sprite[i].distance < m->sprite[j].distance)
			{
				tmp = m->sprite[i];
				m->sprite[i] = m->sprite[j];
				m->sprite[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	sprite_project(t_index *m)
{
	int	i;
	int	j;
	int d;
	
	i = 0;
	while (i < m->cub.nbrsprt)
	{
		m->sprcalc.spr_x = m->sprite[i].x - m->cub.pos.x + 0.5;
		m->sprcalc.spr_y = m->sprite[i].y - m->cub.pos.y + 0.5;
		m->sprcalc.invert = 1 / (m->cub.plane.x * m->cub.dir.y - m->cub.dir.x *
				m->cub.plane.y);
		m->sprcalc.trsfm_x = m->sprcalc.invert * (m->cub.dir.y *
				m->sprcalc.spr_x - m->cub.dir.x * m->sprcalc.spr_y);
		m->sprcalc.trsfm_y = m->sprcalc.invert * (-m->cub.plane.y *
				m->sprcalc.spr_x + m->cub.plane.x * m->sprcalc.spr_y);
		m->sprcalc.sprscreen_x = (int)((m->cub.win.w / 2) *
				(1 + m->sprcalc.trsfm_x / m->sprcalc.trsfm_y));
		m->sprcalc.spr_h = abs((int)(m->cub.win.h / m->sprcalc.trsfm_y));
		m->sprcalc.drawstart_y = -m->sprcalc.spr_h / 2 + m->cub.win.h / 2;
		m->sprcalc.drawstart_y < 0 ? m->sprcalc.drawstart_y = 0 : 0;
		m->sprcalc.drawend_y = m->sprcalc.spr_h / 2 + m->cub.win.h / 2;
		m->sprcalc.drawend_y >= m->cub.win.h ?
			m->sprcalc.drawend_y = m->cub.win.h - 1 : 0;
		m->sprcalc.spr_w = abs((int)(m->cub.win.h / m->sprcalc.trsfm_y));
		m->sprcalc.drawstart_x = -m->sprcalc.spr_w / 2 + m->sprcalc.sprscreen_x;
		m->sprcalc.drawstart_x < 0 ? m->sprcalc.drawstart_x = 0 : 0;
		m->sprcalc.drawend_x = m->sprcalc.spr_w / 2 + m->sprcalc.sprscreen_x;
		m->sprcalc.drawend_x >= m->cub.win.w ?
			m->sprcalc.drawend_x = m->cub.win.w - 1 : 0;
		m->sprcalc.strip = m->sprcalc.drawstart_x;
		while (m->sprcalc.strip < m->sprcalc.drawend_x)
		{
			m->sprcalc.texx = (int)(256 * (m->sprcalc.strip - (-m->sprcalc.spr_w
					/ 2 + m->sprcalc.sprscreen_x)) * m->cub.sprite->size.w
							/ m->sprcalc.spr_w) / 256;
			j = m->sprcalc.drawstart_y;
			if (m->sprcalc.trsfm_y > 0 && m->sprcalc.strip > 0 &&
				m->sprcalc.strip < m->cub.win.w &&
				m->sprcalc.trsfm_y < m->ray.zbuff[m->sprcalc.strip])
				while (j < m->sprcalc.drawend_y)
				{
					d = j * 256 - m->cub.win.h * 128 + m->sprcalc.spr_h * 128;
					m->sprcalc.texy = ((d * m->cub.sprite->size.h) /
							m->sprcalc.spr_h) / 256;
					m->sprcalc.color = &m->cub.sprite->addr[
							m->cub.sprite->size.w * m->sprcalc.texy * 2 +
							m->sprcalc.texx];
					if ((*m->sprcalc.color & 0x00FFFFFF)!= 0)
						m->img.addr[j * m->img.line_length +
							m->sprcalc.strip] = *m->sprcalc.color;
					j++;
				}
			m->sprcalc.strip++;
		}
		i++;
	}
}

void	manage_sprite(t_index *m)
{
	int		i;

	i = 0;
	while (i < m->cub.nbrsprt)
	{
		m->sprite[i].distance = ((m->cub.pos.x - m->sprite[i].x) *
			(m->cub.pos.x - m->sprite[i].x) + (m->cub.pos.y - m->sprite[i].y) *
			(m->cub.pos.y - m->sprite[i].y));
		i++;
	}
	sort_sprite(m);
	sprite_project(m);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 17:37:15 by nsimon            #+#    #+#             */
/*   Updated: 2020/06/13 18:09:30 by nsimon           ###   ########.fr       */
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
	int			j;
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

void	draw_sprite(t_index *m, int j)
{
	int d;

	while (j < m->sprcalc.drawend_y)
	{
		d = j * 256 - m->cub.win.h * 128 + m->sprcalc.spr_h * 128;
		m->sprcalc.texy = ((d * m->cub.sprite->size.h) /
							m->sprcalc.spr_h) / 256;
		if (m->cub.sprite->size.h < 64 && APPLE)
			m->sprcalc.color = &m->cub.sprite->addr[
					m->cub.sprite->size.w * (m->sprcalc.texy * 64 /
					m->cub.sprite->size.h) + m->sprcalc.texx];
		else
			m->sprcalc.color = &m->cub.sprite->addr[
					m->cub.sprite->size.w * m->sprcalc.texy +
					m->sprcalc.texx];
		if ((*m->sprcalc.color & 0x00FFFFFF) != 0)
			m->img.addr[j * m->img.line_length +
						m->sprcalc.strip] = *m->sprcalc.color;
		j++;
	}
}

void	sprite_project(t_index *m)
{
	int	i;
	int	j;

	i = 0;
	while (i < m->cub.nbrsprt)
	{
		init_sprite(m, i);
		while (m->sprcalc.strip < m->sprcalc.drawend_x)
		{
			m->sprcalc.texx = (int)(256 * (m->sprcalc.strip - (-m->sprcalc.spr_w
					/ 2 + m->sprcalc.sprscreen_x)) * m->cub.sprite->size.w
							/ m->sprcalc.spr_w) / 256;
			j = m->sprcalc.drawstart_y;
			if (m->sprcalc.trsfm_y > 0 && m->sprcalc.strip > 0 &&
					m->sprcalc.strip < m->cub.win.w &&
					m->sprcalc.trsfm_y < m->ray.zbuff[m->sprcalc.strip])
				draw_sprite(m, j);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 17:45:34 by nsimon            #+#    #+#             */
/*   Updated: 2020/06/13 18:05:40 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_move_init(t_index *m)
{
	m->move.esc = 0;
	m->move.left = 0;
	m->move.turn_left = 0;
	m->move.right = 0;
	m->move.turn_right = 0;
	m->move.back = 0;
	m->move.foward = 0;
}

void	init_cub(t_index *m)
{
	if ((m->cub.m_ptr = mlx_init()) == NULL)
		ft_error(14);
	m->cub.save = 0;
	m->cub.win.w = 0;
	m->cub.win.h = 0;
	if ((m->cub.map = malloc(sizeof(m->cub.map))) == NULL)
		ft_error(99);
	m->cub.map[0] = ft_strdup("");
	m->cub.pos.x = -1;
	m->cub.pos.y = -1;
	m->cub.dir.x = -1;
	m->cub.dir.y = 0;
	m->cub.plane.x = 0;
	m->cub.plane.y = 0.66;
	m->cub.no = NULL;
	m->cub.so = NULL;
	m->cub.ea = NULL;
	m->cub.we = NULL;
	m->cub.sprite = NULL;
	m->cub.sol = -1;
	m->cub.plafond = -1;
}

void	init_sprite(t_index *m, int i)
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
}

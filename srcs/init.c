/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 17:45:34 by nsimon            #+#    #+#             */
/*   Updated: 2020/06/13 17:29:33 by nsimon           ###   ########.fr       */
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
}
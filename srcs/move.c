/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 20:37:44 by nsimon            #+#    #+#             */
/*   Updated: 2020/06/13 19:32:42 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	go_up_down(t_index *m, int direction)
{
	t_cub	*cub;
	float	movespeed;

	cub = &m->cub;
	movespeed = MOVE_SPEED + m->move.movespeed;
	if (direction == 0)
	{
		if (cub->map[(int)(cub->pos.x + cub->dir.x * (movespeed + 0.1))]
			[(int)cub->pos.y] != '1')
			cub->pos.x += cub->dir.x * movespeed;
		if (cub->map[(int)cub->pos.x]
			[(int)(cub->pos.y + cub->dir.y * (movespeed + 0.1))] != '1')
			cub->pos.y += cub->dir.y * movespeed;
	}
	else
	{
		if (cub->map[(int)(cub->pos.x - cub->dir.x * (movespeed + 0.1))]
			[(int)cub->pos.y] != '1')
			cub->pos.x -= cub->dir.x * movespeed;
		if (cub->map[(int)cub->pos.x]
			[(int)(cub->pos.y - cub->dir.y * (movespeed + 0.1))] != '1')
			cub->pos.y -= cub->dir.y * movespeed;
	}
}

void	go_left_right(t_index *m, int direction)
{
	t_cub	*cub;
	float	movespeed;

	cub = &m->cub;
	movespeed = MOVE_SPEED + m->move.movespeed;
	if (direction == 0)
	{
		if (cub->map[(int)(cub->pos.x - cub->plane.x * (movespeed + 0.1))]
			[(int)cub->pos.y] != '1')
			cub->pos.x -= cub->plane.x * movespeed;
		if (cub->map[(int)cub->pos.x]
			[(int)(cub->pos.y - cub->plane.y * (movespeed + 0.1))] != '1')
			cub->pos.y -= cub->plane.y * movespeed;
	}
	else
	{
		if (cub->map[(int)(cub->pos.x + cub->plane.x * (movespeed + 0.1))]
			[(int)cub->pos.y] != '1')
			cub->pos.x += cub->plane.x * movespeed;
		if (cub->map[(int)cub->pos.x]
			[(int)(cub->pos.y + cub->plane.y * (movespeed + 0.1))] != '1')
			cub->pos.y += cub->plane.y * movespeed;
	}
}

void	go_turn_left_right(t_cub *cub, int direction)
{
	double	old_d_x;
	double	old_p_x;
	float	rotspeed;

	old_d_x = cub->dir.x;
	old_p_x = cub->plane.x;
	rotspeed = ROTATE_SPEED;
	if (direction == 0)
	{
		cub->dir.x = cub->dir.x * cos(rotspeed) - cub->dir.y * sin(rotspeed);
		cub->dir.y = old_d_x * sin(rotspeed) + cub->dir.y * cos(rotspeed);
		cub->plane.x = cub->plane.x * cos(rotspeed) - cub->plane.y *
				sin(rotspeed);
		cub->plane.y = old_p_x * sin(rotspeed) + cub->plane.y * cos(rotspeed);
	}
	else
	{
		cub->dir.x = cub->dir.x * cos(-rotspeed) - cub->dir.y * sin(-rotspeed);
		cub->dir.y = old_d_x * sin(-rotspeed) + cub->dir.y * cos(-rotspeed);
		cub->plane.x = cub->plane.x * cos(-rotspeed) - cub->plane.y *
				sin(-rotspeed);
		cub->plane.y = old_p_x * sin(-rotspeed) + cub->plane.y * cos(-rotspeed);
	}
}

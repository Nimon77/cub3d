/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 20:37:44 by nsimon            #+#    #+#             */
/*   Updated: 2020/05/26 17:22:43 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	go_up_down(t_cub *cub, int direction)
{
	float moveSpeed = MOVE_SPEED;
	
	if (direction == 0)
	{
		if (cub->map[(int) (cub->pos.x + cub->dir.x * (moveSpeed + 0.1))]
			[(int) cub->pos.y] != '1')
			cub->pos.x += cub->dir.x * moveSpeed;
		if (cub->map[(int) cub->pos.x]
			[(int) (cub->pos.y + cub->dir.y * (moveSpeed + 0.1))] != '1')
			cub->pos.y += cub->dir.y * moveSpeed;
	}
	else
	{
		if (cub->map[(int)(cub->pos.x - cub->dir.x * (moveSpeed + 0.1))]
			[(int)cub->pos.y] != '1')
			cub->pos.x -= cub->dir.x * moveSpeed;
		if (cub->map[(int)cub->pos.x]
			[(int)(cub->pos.y - cub->dir.y * (moveSpeed + 0.1))] != '1')
			cub->pos.y -= cub->dir.y * moveSpeed;
	}
}

void	go_left_right(t_cub *cub, int direction)
{
	float	moveSpeed = MOVE_SPEED;
	
	if (direction == 0)
	{
		if (cub->map[(int) (cub->pos.x - cub->plane.x * (moveSpeed + 0.1))]
			[(int) cub->pos.y] != '1')
			cub->pos.x -= cub->plane.x * moveSpeed;
		if (cub->map[(int) cub->pos.x]
			[(int) (cub->pos.y - cub->plane.y * (moveSpeed + 0.1))] != '1')
			cub->pos.y -= cub->plane.y * moveSpeed;
	}
	else
	{
		if (cub->map[(int)(cub->pos.x + cub->plane.x * (moveSpeed + 0.1))]
			[(int)cub->pos.y] != '1')
			cub->pos.x += cub->plane.x * moveSpeed;
		if (cub->map[(int)cub->pos.x]
			[(int)(cub->pos.y + cub->plane.y * (moveSpeed + 0.1))] != '1')
			cub->pos.y += cub->plane.y * moveSpeed;
	}
}

void	go_turn_left_right(t_cub *cub, int direction)
{
	double old_d_x = cub->dir.x;
	double old_p_x = cub->plane.x;
	float rotSpeed = ROTATE_SPEED;
	
	if (direction == 0)
	{
		cub->dir.x = cub->dir.x * cos(rotSpeed) - cub->dir.y * sin(rotSpeed);
		cub->dir.y = old_d_x * sin(rotSpeed) + cub->dir.y * cos(rotSpeed);
		cub->plane.x = cub->plane.x * cos(rotSpeed) - cub->plane.y *
				sin(rotSpeed);
		cub->plane.y = old_p_x * sin(rotSpeed) + cub->plane.y * cos(rotSpeed);
	}
	else
	{
		cub->dir.x = cub->dir.x * cos(-rotSpeed) - cub->dir.y * sin(-rotSpeed);
		cub->dir.y = old_d_x * sin(-rotSpeed) + cub->dir.y * cos(-rotSpeed);
		cub->plane.x = cub->plane.x * cos(-rotSpeed) - cub->plane.y *
				sin(-rotSpeed);
		cub->plane.y = old_p_x * sin(-rotSpeed) + cub->plane.y * cos(-rotSpeed);
	}
}

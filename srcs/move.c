/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 20:37:44 by nsimon            #+#    #+#             */
/*   Updated: 2020/05/18 16:55:09 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	go_up(t_cub *cub)
{
	int moveSpeed = 5;
	
	if (cub->map[(int)(cub->plane.x + cub->dir.x * moveSpeed)][(int)
			cub->plane.y] == '0')
		cub->plane.x += cub->dir.x * moveSpeed;
	if (cub->map[(int)cub->plane.x][(int)(cub->plane.y + cub->dir.y *
			moveSpeed)] == '0')
		cub->plane.y += cub->dir.y * moveSpeed;
}

void	go_down(t_cub *cub)
{
	int moveSpeed = 5;
	
	if (cub->map[(int)(cub->plane.x + cub->dir.x * moveSpeed)][(int)
			cub->plane.y] == '0')
		cub->plane.x -= cub->dir.x * moveSpeed;
	if (cub->map[(int)cub->plane.x][(int)(cub->plane.y + cub->dir.y *
			moveSpeed)] == '0')
		cub->plane.y -= cub->dir.y * moveSpeed;
}

void	go_left(t_cub *cub)
{
	double old_d_x = cub->dir.x;
	double old_p_x = cub->plane.x;
	int rotSpeed = 1;
	
	cub->dir.x = cub->dir.x * cos(rotSpeed) - cub->dir.y * sin(rotSpeed);
	cub->dir.y = old_d_x * sin(rotSpeed) + cub->dir.y * cos(rotSpeed);
	
	cub->plane.x = cub->plane.x * cos(rotSpeed) - cub->plane.y * sin(rotSpeed);
	cub->plane.y = old_p_x * sin(rotSpeed) + cub->plane.y * cos(rotSpeed);
}

void	go_right(t_cub *cub)
{
	double	old_d_x = cub->dir.x;
	double	old_p_x = cub->plane.x;
	int rotSpeed = 1;
	
	cub->dir.x = cub->dir.x * cos(-rotSpeed) - cub->dir.y * sin(-rotSpeed);
	cub->dir.y = old_d_x * sin(-rotSpeed) + cub->dir.y * cos(-rotSpeed);
	
	cub->plane.x = cub->plane.x * cos(-rotSpeed) - cub->plane.y * sin(-rotSpeed);
	cub->plane.y = old_p_x * sin(-rotSpeed) + cub->plane.y * cos(-rotSpeed);
}
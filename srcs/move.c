/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 20:37:44 by nsimon            #+#    #+#             */
/*   Updated: 2020/02/26 20:44:18 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	go_up(cub_t *cub)
{
	int moveSpeed = 5;
	
	if (cub->map[(int)(cub->p_x + cub->d_x * moveSpeed)][(int)cub->p_y] == '0')
		cub->p_x += cub->d_x * moveSpeed;
	if (cub->map[(int)cub->p_x][(int)(cub->p_y + cub->d_y * moveSpeed)] == '0')
		cub->p_y += cub->d_y * moveSpeed;
}

void	go_down(cub_t *cub)
{
	int moveSpeed = 5;
	
	if (cub->map[(int)(cub->p_x + cub->d_x * moveSpeed)][(int)cub->p_y] == '0')
		cub->p_x -= cub->d_x * moveSpeed;
	if (cub->map[(int)cub->p_x][(int)(cub->p_y + cub->d_y * moveSpeed)] == '0')
		cub->p_y -= cub->d_y * moveSpeed;
}

void	go_right(cub_t *cub)
{
	double	old_d_x = cub->d_x;
	double	old_p_x = cub->p_x;
	int rotSpeed = 3;
	
	cub->d_x = cub->d_x * cos(-rotSpeed) - cub->d_y * sin(-rotSpeed);
	cub->d_y = old_d_x * sin(-rotSpeed) + cub->d_y * cos(-rotSpeed);
	
	cub->p_x = cub->p_x * cos(-rotSpeed) - cub->p_y * sin(-rotSpeed);
	cub->p_y = old_p_x * sin(-rotSpeed) + cub->p_y * cos(-rotSpeed);
}

void	go_left(cub_t *cub)
{
	double old_d_x = cub->d_x;
	double old_p_x = cub->p_x;
	int rotSpeed = 3;
	
	cub->d_x = cub->d_x * cos(rotSpeed) - cub->d_y * sin(rotSpeed);
	cub->d_y = old_d_x * sin(rotSpeed) + cub->d_y * cos(rotSpeed);
	
	cub->p_x = cub->p_x * cos(rotSpeed) - cub->p_y * sin(rotSpeed);
	cub->p_y = old_p_x * sin(rotSpeed) + cub->p_y * cos(rotSpeed);
}

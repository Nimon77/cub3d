/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 20:37:44 by nsimon            #+#    #+#             */
/*   Updated: 2020/02/25 20:55:53 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/*
void	go_up(cub_t *cub)
{
	int moveSpeed = 5;
	
	if (cub->map[cub->p_x + cub->d_x * moveSpeed][cub->p_y] == '0')
		cub->p_x += cub->d_x * moveSpeed;
	if (cub->map[cub->p_x][cub->p_y + cub->d_y * moveSpeed] == '0')
		cub->p_y += cub->d_y * moveSpeed;
}

void	go_down(cub_t *cub)
{
	int moveSpeed = 5;
	
	if (cub->map[cub->p_x + cub->d_x * moveSpeed][cub->p_y] == '0')
		cub->p_x -= cub->d_x * moveSpeed;
	if (cub->map[cub->p_x][cub->p_y + cub->d_y * moveSpeed] == '0')
		cub->p_y -= cub->d_y * moveSpeed;
}

void	go_right(cub_t *cub)
{
	int old_d_x = cub->d_x;
	int old_p_x = cub->p_x;
	int rotSpeed = 3;
	
	cub->d_x = cub->d_x * cos(-rotSpeed) - cub->d_y * sin(-rotSpeed);
	cub->d_y = old_d_x * sin(-rotSpeed) + cub->d_y * cos(-rotSpeed);
	
	cub->p_x = cub->p_x * cos(-rotSpeed) - cub->p_y * sin(-rotSpeed);
	cub->p_y = old_p_x * sin(-rotSpeed) + cub->p_y * cos(-rotSpeed);
}

void	go_left(cub_t *cub)
{
	int old_d_x = cub->d_x;
	int old_p_x = cub->p_x;
	int rotSpeed = 3;
	
	cub->d_x = cub->d_x * cos(rotSpeed) - cub->d_y * sin(rotSpeed);
	cub->d_y = old_d_x * sin(rotSpeed) + cub->d_y * cos(rotSpeed);
	
	cub->p_x = cub->p_x * cos(rotSpeed) - cub->p_y * sin(rotSpeed);
	cub->p_y = old_p_x * sin(rotSpeed) + cub->p_y * cos(rotSpeed);
}
*/
void	quit(cub_t *cub)
{
	printf("quit\n");
	mlx_destroy_window(cub->m_ptr, cub->m_win);
	mlx_destroy_image(cub->m_ptr, cub->NO->img);
	mlx_destroy_image(cub->m_ptr, cub->EA->img);
	mlx_destroy_image(cub->m_ptr, cub->SO->img);
	mlx_destroy_image(cub->m_ptr, cub->WE->img);
	mlx_destroy_image(cub->m_ptr, cub->sprite->img);
	ft_free_matrice(cub->map);
	system("leaks cub3d");
	exit(0);
}

int		ft_move(int keycode, void *param)
{
	printf("%d\n", keycode);
	keycode == 13 ? printf("up\n") : 0;
	keycode == 1 ? printf("down\n") : 0;
	keycode == 0 ? printf("left\n") : 0;
	keycode == 2 ? printf("right\n") : 0;
	keycode == 12 ? quit((cub_t *)param) : 0;
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 20:47:40 by nsimon            #+#    #+#             */
/*   Updated: 2020/06/06 16:45:36 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	quit(t_index *m)
{
	printf("quit\n");
	mlx_destroy_window(m->cub.m_ptr, m->cub.m_win);
	mlx_destroy_image(m->cub.m_ptr, m->cub.no->img);
	mlx_destroy_image(m->cub.m_ptr, m->cub.ea->img);
	mlx_destroy_image(m->cub.m_ptr, m->cub.so->img);
	mlx_destroy_image(m->cub.m_ptr, m->cub.we->img);
	mlx_destroy_image(m->cub.m_ptr, m->cub.sprite->img);
	mlx_destroy_image(m->cub.m_ptr, m->img.img);
	ft_free_matrice(m->cub.map);
	free(m->sprite);
	system("leaks cub3d");
	exit(0);
}

int	ft_release(int keycode, t_move *move)
{
	if (keycode == 53)
		move->esc = 0;
	else if (keycode == 13)
		move->foward = 0;
	else if (keycode == 1)
		move->back = 0;
	else if (keycode == 0)
		move->left = 0;
	else if (keycode == 2)
		move->right = 0;
	else if (keycode == 123)
		move->turn_left = 0;
	else if (keycode == 124)
		move->turn_right = 0;
	return (0);
}

int	ft_press(int keycode, t_move *move)
{
	if (keycode == 53)
		move->esc = 1;
	else if (keycode == 13)
		move->foward = 1;
	else if (keycode == 1)
		move->back = 1;
	else if (keycode == 0)
		move->left = 1;
	else if (keycode == 2)
		move->right = 1;
	else if (keycode == 123)
		move->turn_left = 1;
	else if (keycode == 124)
		move->turn_right = 1;
	return (0);
}

int	ft_move(t_index *m)
{
	m->move.foward == 1 ? go_up_down(&m->cub, 0) : 0;
	m->move.back == 1 ? go_up_down(&m->cub, 1) : 0;
	m->move.left == 1 ? go_left_right(&m->cub, 0) : 0;
	m->move.right == 1 ? go_left_right(&m->cub, 1) : 0;
	m->move.turn_left == 1 ? go_turn_left_right(&m->cub, 0) : 0;
	m->move.turn_right == 1 ? go_turn_left_right(&m->cub, 1) : 0;
	m->move.esc == 1 ? quit(m) : 0;
	return (0);
}
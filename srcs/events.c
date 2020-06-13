/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 20:47:40 by nsimon            #+#    #+#             */
/*   Updated: 2020/06/13 17:29:10 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	quit(t_index *m)
{
	!m->cub.save ? mlx_destroy_window(m->cub.m_ptr, m->cub.m_win) : 0;
	mlx_destroy_image(m->cub.m_ptr, m->cub.no->img);
	mlx_destroy_image(m->cub.m_ptr, m->cub.ea->img);
	mlx_destroy_image(m->cub.m_ptr, m->cub.so->img);
	mlx_destroy_image(m->cub.m_ptr, m->cub.we->img);
	mlx_destroy_image(m->cub.m_ptr, m->cub.sprite->img);
	ft_free_matrice(m->cub.map);
	free(m->sprite);
	system("leaks cub3d");
	exit(0);
}

int	ft_release(int keycode, t_move *move)
{
	if (keycode == ESC)
		move->esc = 0;
	else if (keycode == FORWARD)
		move->foward = 0;
	else if (keycode == BACK)
		move->back = 0;
	else if (keycode == LEFT)
		move->left = 0;
	else if (keycode == RIGHT)
		move->right = 0;
	else if (keycode == TURNLEFT)
		move->turn_left = 0;
	else if (keycode == TURNRIGHT)
		move->turn_right = 0;
	else if (keycode == SPRINT)
		move->moveSpeed = 0;
	printf("%d\n", keycode);
	return (0);
}

int	ft_press(int keycode, t_move *move)
{
	if (keycode == ESC)
		move->esc = 1;
	else if (keycode == FORWARD)
		move->foward = 1;
	else if (keycode == BACK)
		move->back = 1;
	else if (keycode == LEFT)
		move->left = 1;
	else if (keycode == RIGHT)
		move->right = 1;
	else if (keycode == TURNLEFT)
		move->turn_left = 1;
	else if (keycode == TURNRIGHT)
		move->turn_right = 1;
	else if (keycode == SPRINT)
		move->moveSpeed = 0.1;
	return (0);
}

int	ft_move(t_index *m)
{
	m->move.foward == 1 ? go_up_down(m, 0) : 0;
	m->move.back == 1 ? go_up_down(m, 1) : 0;
	m->move.left == 1 ? go_left_right(m, 0) : 0;
	m->move.right == 1 ? go_left_right(m, 1) : 0;
	m->move.turn_left == 1 ? go_turn_left_right(&m->cub, 0) : 0;
	m->move.turn_right == 1 ? go_turn_left_right(&m->cub, 1) : 0;
	m->move.esc == 1 ? quit(m) : 0;
	return (0);
}

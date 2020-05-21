/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 20:47:40 by nsimon            #+#    #+#             */
/*   Updated: 2020/05/18 17:02:59 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		quit(t_cub *cub)
{
	printf("quit\n");
	mlx_destroy_window(cub->m_ptr, cub->m_win);
	mlx_destroy_image(cub->m_ptr, cub->no->img);
	mlx_destroy_image(cub->m_ptr, cub->ea->img);
	mlx_destroy_image(cub->m_ptr, cub->so->img);
	mlx_destroy_image(cub->m_ptr, cub->we->img);
	mlx_destroy_image(cub->m_ptr, cub->sprite->img);
	ft_free_matrice(cub->map);
	//system("leaks cub3d");
	exit(0);
}

int		ft_move(int keycode, t_index *m)
{
	printf("%d\n", keycode);
	keycode == 13 ? go_up(&m->cub) : 0;
	keycode == 1 ? go_down(&m->cub) : 0;
	keycode == 0 ? go_left(&m->cub) : 0;
	keycode == 2 ? go_right(&m->cub) : 0;
	keycode == 12 || keycode == 53 ? quit(&m->cub) : 0;
	raycast(m);
	return (0);
}
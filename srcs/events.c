/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 20:47:40 by nsimon            #+#    #+#             */
/*   Updated: 2020/02/27 15:43:10 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		quit(cub_t *cub)
{
	printf("quit\n");
	mlx_destroy_window(cub->m_ptr, cub->m_win);
	mlx_destroy_image(cub->m_ptr, cub->NO->img);
	mlx_destroy_image(cub->m_ptr, cub->EA->img);
	mlx_destroy_image(cub->m_ptr, cub->SO->img);
	mlx_destroy_image(cub->m_ptr, cub->WE->img);
	mlx_destroy_image(cub->m_ptr, cub->sprite->img);
	ft_free_matrice(cub->map);
	//system("leaks cub3d");
	exit(0);
}

int		ft_move(int keycode, cub_t *cub)
{
	printf("%d\n", keycode);
	keycode == 13 ? go_up(cub) : 0;
	keycode == 1 ? go_down(cub) : 0;
	keycode == 0 ? go_left(cub) : 0;
	keycode == 2 ? go_right(cub) : 0;
	keycode == 12 || keycode == 53 ? quit(cub) : 0;
	ft_actual(cub);
	return (0);
}

int 	ft_actual(cub_t * cub)
{
	
	mlx_loop(cub->m_ptr);
	return (0);
}
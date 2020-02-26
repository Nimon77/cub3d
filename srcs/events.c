/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 20:47:40 by nsimon            #+#    #+#             */
/*   Updated: 2020/02/26 20:48:09 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	//system("leaks cub3d");
	exit(0);
}

int		ft_move(int keycode, cub_t *cub)
{
	printf("%d\n", keycode);
	//keycode == 13 ? printf("up\n") : 0;
	keycode == 13 ? put_color(cub->plafond, cub) : 0;
	//keycode == 1 ? printf("down\n") : 0;
	keycode == 1 ? put_color(cub->sol, cub) : 0;
	keycode == 0 ? printf("left\n") : 0;
	keycode == 2 ? printf("right\n") : 0;
	keycode == 12 || keycode == 53 ? quit(cub) : 0;
	return (0);
}

int 	ft_actual(cub_t * cub)
{
	mlx_loop(cub->m_ptr);
	return (0);
}
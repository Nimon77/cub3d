/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 20:59:09 by nsimon            #+#    #+#             */
/*   Updated: 2020/03/10 16:54:06 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_raycast(raycast_t *raycst, cub_t *cub)
{
	raycst->camera = 2 * raycst->x / (double)cub->width - 1;
	raycst->ray.x = cub->dir.x + cub->plane.x * raycst->camera;
	raycst->ray.y = cub->dir.y + cub->plane.y * raycst->camera;
	raycst->map.x = (int)cub->plane.x;
	raycst->map.y = (int)cub->plane.y;
	raycst->delta.x = sqrt(1 + (raycst->ray.y * raycst->ray.y) / (raycst->ray.x
			* raycst->ray.x));
	raycst->delta.y = sqrt(1 + (raycst->ray.x * raycst->ray.x) / (raycst->ray.y
			* raycst->ray.y));
	raycst->hit = 0;
}

int 	raycast(cub_t *cub)
{
	raycast_t	raycst;
	
	raycst.x = 0;
	mlx_clear_window(cub->m_ptr, cub->m_win);
	while (raycst.x < cub->width)
	{
		init_raycast(&raycst, cub);

		
		
	//	while (drawStart < drawEnd)
	//		mlx_pixel_put(cub->m_ptr, cub->m_win, x, drawStart++, color);
		raycst.x++;
	}
	mlx_loop(cub->m_ptr);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 20:59:09 by nsimon            #+#    #+#             */
/*   Updated: 2020/05/18 16:50:36 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_raycast(t_raycast *raycst, t_cub *cub)
{
	raycst->camera = 2 * raycst->x / (double)cub->win.w - 1;
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

int 	raycast(t_cub *cub)
{
	mlx_clear_window(cub->m_ptr, cub->m_win);
	for(int x = 0; x < cub->win.w; x++)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)cub->win.w - 1; //x-coordinate in
		// camera space
		double rayDirX = cub->dir.x + cub->plane.x * cameraX;
		double rayDirY = cub->dir.y + cub->plane.y * cameraX;
		//which box of the map we're in
		int mapX = (int)cub->pos.x;
		int mapY = (int)cub->pos.y;
		
		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;
		
		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = ABS(1 / rayDirX);
		double deltaDistY = ABS(1 / rayDirY);
		double perpWallDist;
		
		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;
		
		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (cub->pos.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - cub->pos.x) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (cub->pos.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - cub->pos.y) * deltaDistY;
		}
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if(sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if(cub->map[mapX][mapY] > '0') hit = 1;
		}
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if (side == 0)
			perpWallDist = (mapX - cub->pos.x + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - cub->pos.y + (1 - stepY) / 2) / rayDirY;
		
		//Calculate height of line to draw on screen
		int lineHeight = (int)(cub->win.h / perpWallDist);
		//int lineHeight = (int)(cub->win.h / 0.3);
		
		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + cub->win.h / 2;
		if(drawStart < 0)drawStart = 0;
		int drawEnd = lineHeight / 2 + cub->win.h / 2;
		if(drawEnd >= cub->win.h)drawEnd = cub->win.h - 1;
		
		//choose wall color
		int color;
		switch(cub->map[mapX][mapY])
		{
			case '1':
				color = 16711680;
				break; //red
			case '2':
				color = 65280;
				break; //green
			case '3':
				color = 255;
				break; //blue
			case '4':
				color = 16777215;
				break; //white
			default:
				color = 16776960;
				break; //yellow
		}
		
		//give x and y sides different brightness
		if(side == 1) {color = color / 2;}
		
		//draw the pixels of the stripe as a vertical line
		for (int i = drawStart; i < drawEnd; i++)
		{
			mlx_pixel_put(cub->m_ptr, cub->m_win, x, i, color);
			//printf("x : %d, i : %d, color : %d", x, i, color);
		}
		//mlx_pixel_put(x, drawStart, drawEnd, color);
	}
}

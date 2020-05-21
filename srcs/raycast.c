/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 20:59:09 by nsimon            #+#    #+#             */
/*   Updated: 2020/05/21 18:12:30 by nsimon           ###   ########.fr       */
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


void	write_img(t_index *m, int drawStart, int drawEnd, int x, int color)
{
	int i;
	
	i = 0;
	while (i < drawStart)
	{
		m->img.addr[i * m->cub.win.w + x] = m->cub.plafond;
		i++;
	}
	while (i < drawEnd)
	{
		m->img.addr[i * m->cub.win.w + x] = color;
		i++;
	}
	while (i < m->cub.win.h)
	{
		m->img.addr[i * m->cub.win.w + x] = m->cub.sol;
		i++;
	}
}

int 	raycast(t_index *m)
{
	//mlx_clear_window(m->cub.m_ptr, m->cub.m_win);
	for(int x = 0; x < m->cub.win.w; x++)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)m->cub.win.w - 1; //x-coordinate in
		// camera space
		double rayDirX = m->cub.dir.x + m->cub.plane.x * cameraX;
		double rayDirY = m->cub.dir.y + m->cub.plane.y * cameraX;
		//which box of the map we're in
		int mapX = (int)m->cub.pos.x;
		int mapY = (int)m->cub.pos.y;
		
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
			sideDistX = (m->cub.pos.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - m->cub.pos.x) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (m->cub.pos.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - m->cub.pos.y) * deltaDistY;
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
			if(m->cub.map[mapX][mapY] != '0') hit = 1;
		}
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if (side == 0)
			perpWallDist = (mapX - m->cub.pos.x + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - m->cub.pos.y + (1 - stepY) / 2) / rayDirY;
		
		//Calculate height of line to draw on screen
		int lineHeight = (int)(m->cub.win.h / perpWallDist);
		//int lineHeight = (int)(m->cub->win.h / 0.3);
		
		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + m->cub.win.h / 2;
		if(drawStart < 0)drawStart = 0;
		int drawEnd = lineHeight / 2 + m->cub.win.h / 2;
		if(drawEnd >= m->cub.win.h)drawEnd = m->cub.win.h - 1;
		
		//choose wall color
		int color;
		switch(m->cub.map[mapX][mapY])
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
		
		write_img(m, drawStart, drawEnd, x, color);
		//mlx_pixel_put(x, drawStart, drawEnd, color);
	}
	mlx_put_image_to_window(m->cub.m_ptr, m->cub.m_win, m->img.img, 0, 0);
}

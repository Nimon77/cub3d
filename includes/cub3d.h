/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 11:47:59 by nsimon            #+#    #+#             */
/*   Updated: 2020/03/10 16:25:43 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include	<stdio.h>
#include	<math.h>
#include	<fcntl.h>

#include	"libft.h"
#include	"mlx.h"

typedef struct	color_s
{
	int			R;
	int			V;
	int			B;
}				color_t;

typedef struct	image_s
{
	void		*img;
	int			wdt;
	int			height;
}				image_t;

typedef struct	coord_dbl_s
{
	double	x;
	double	y;
}				coord_dbl_t;

typedef struct	coord_int_s
{
	int			x;
	int 		y;
}				coord_int_t;

typedef struct	cub_s
{
	void		*m_ptr;
	void		*m_win;
	int			width;
	int			height;
	image_t		*NO;
	image_t		*EA;
	image_t		*SO;
	image_t		*WE;
	image_t		*sprite;
	char 		**map;
	int			sol;
	int			plafond;
	coord_dbl_t	pos;
	coord_dbl_t	plane;
	coord_dbl_t	dir;
}				cub_t;

typedef struct	raycast_s
{
	int			x;
	coord_int_t	map;
	coord_dbl_t	ray;
	coord_dbl_t	delta;
	coord_dbl_t	side;
	coord_int_t	step;
	double		WallDist;
	double		camera;
	int 		hit;
}				raycast_t;

int				quit(cub_t *cub);
void			ft_error(int error);
void			ft_free_matrice(char **str);
void			ft_parse(cub_t *cub, char *path);
void			put_color(int color, cub_t *cub);
int 			ft_actual(cub_t * cub);
int 			raycast(cub_t *cub);
void			go_up(cub_t *cub);
void			go_down(cub_t *cub);
void			go_left(cub_t *cub);
void			go_right(cub_t *cub);
int				ft_move(int keycode, cub_t *cub);

#endif

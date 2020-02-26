/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 11:47:59 by nsimon            #+#    #+#             */
/*   Updated: 2020/02/26 20:35:14 by nsimon           ###   ########.fr       */
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
	double		p_x;
	double		p_y;
	double		d_x;
	double		d_y;
	int 		m_x;
	int 		m_y;
	int 		hit;
}				cub_t;

void			ft_error(int error);
void			ft_free_matrice(char **str);
void			ft_parse(cub_t *cub, char *path);
void			put_color(int color, cub_t *cub);
int 			ft_actual(cub_t * cub);
int				ft_move(int keycode, cub_t *cub);

#endif

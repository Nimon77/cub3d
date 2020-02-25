/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 11:47:59 by nsimon            #+#    #+#             */
/*   Updated: 2020/02/25 19:33:55 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include	<stdio.h>
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
	double
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
	int 		p_x;
	int 		p_y;
	int 		d_x;
	int 		d_y;
	int 		m_x;
	int 		m_y;
}				cub_t;

void			ft_error(int error);
void			ft_parse(cub_t *cub, char *path);

#endif

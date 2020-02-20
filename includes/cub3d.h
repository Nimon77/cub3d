/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 11:47:59 by nsimon            #+#    #+#             */
/*   Updated: 2020/02/20 12:01:51 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

typedef struct	data_s
{
	void		*mlx_ptr;
	void		*mlx_win;
}				data_t;

typedef struct	color_s
{
	int 		R;
	int 		G;
	int 		B;
}				color_t;

typedef struct	cub_s
{
	int 		width;
	int 		height;
	char 		*NO;
	char 		*EA;
	char 		*SO;
	char		*WE;
	char 		*sprite;
	color_t		sol;
	color_t		plafond;
}				cub_t;

#endif

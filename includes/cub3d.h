/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 11:47:59 by nsimon            #+#    #+#             */
/*   Updated: 2020/02/21 21:36:51 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include	"libft.h"
#include	"mlx.h"

typedef struct	color_s
{
	char	R[4];
	char	V[4];
	char	B[4];
}				color_t;

typedef struct	cub_s
{
	void		*m_ptr;
	void		*m_win;
	int			width;
	int			height;
	void		*NO;
	void		*EA;
	void		*SO;
	void		*WE;
	void 		*sprite;
	t_list 		*map;
	int			sol;
	int			plafond;
}				cub_t;

void	ft_parse(char *str, cub_t *cub);

#endif

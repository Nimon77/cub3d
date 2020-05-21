/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 11:47:59 by nsimon            #+#    #+#             */
/*   Updated: 2020/05/21 17:30:56 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include <fcntl.h>

# include "libft.h"
# include "mlx.h"

typedef struct	s_color
{
	int			r;
	int			v;
	int			b;
}				t_color;

typedef struct	s_tex
{
	void		*img;
	int			wdt;
	int			height;
}				t_tex;

typedef struct	s_coord_dbl
{
	double	x;
	double	y;
}				t_coord_dbl;

typedef struct	s_coord_int
{
	int			x;
	int			y;
}				t_coord_int;

typedef struct	s_cub
{
	void		*m_ptr;
	void		*m_win;
	struct
	{
		int		w;
		int		h;
	}			win;
	t_tex		*no;
	t_tex		*ea;
	t_tex		*so;
	t_tex		*we;
	t_tex		*sprite;
	char		**map;
	int			sol;
	int			plafond;
	t_coord_dbl	pos;
	t_coord_dbl	plane;
	t_coord_dbl	dir;
}				t_cub;

typedef struct	s_raycast
{
	int			x;
	t_coord_int	map;
	t_coord_dbl	ray;
	t_coord_dbl	delta;
	t_coord_dbl	side;
	t_coord_int	step;
	double		walldist;
	double		camera;
	int			hit;
}				t_raycast;

typedef struct	s_image
{
	void	*img;
	int		*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_image;

typedef struct	s_index
{
	t_image		img;
	t_cub		cub;
}				t_index;

int				quit(t_cub *cub);
void			ft_error(int error);
void			ft_free_matrice(char **str);
void			ft_parse(t_cub *cub, char *path);
void			put_color(int color, t_cub *cub);
int				ft_actual(t_cub *cub);
int				get_color(char *str);
int				raycast(t_index *m);
void			go_up(t_cub *cub);
void			go_down(t_cub *cub);
void			go_left(t_cub *cub);
void			go_right(t_cub *cub);
void 			check_map(t_cub *cub);
int				ft_move(int keycode, t_index *m);

#endif

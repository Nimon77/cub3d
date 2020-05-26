/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 11:47:59 by nsimon            #+#    #+#             */
/*   Updated: 2020/05/26 15:37:02 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include <fcntl.h>

# include "libft.h"
# include "mlx.h"

# define PRESS_EVENT 2
# define PRESS_MASK 1
# define RELEASE_EVENT 3
# define RELEASE_MASK 2
# define MOVE_SPEED 0.05
# define ROTATE_SPEED 0.03

typedef struct	s_color
{
	int			r;
	int			v;
	int			b;
}				t_color;

typedef struct	s_coord_dbl
{
	double		x;
	double		y;
}				t_coord_dbl;

typedef struct	s_image
{
	void		*img;
	int			*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_image;

typedef struct	s_texture
{
	void		*img;
	int			*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	struct
	{
		int		w;
		int		h;
	}			size;
}				t_texture;

typedef struct	s_cub
{
	void		*m_ptr;
	void		*m_win;
	struct
	{
		int		w;
		int		h;
	}			win;
	t_texture	*no;
	t_texture	*ea;
	t_texture	*so;
	t_texture	*we;
	t_texture	*sprite;
	char		**map;
	int			sol;
	int			plafond;
	t_coord_dbl	pos;
	t_coord_dbl	plane;
	t_coord_dbl	dir;
}				t_cub;

typedef struct	s_move
{
	int			esc;
	int			foward;
	int			back;
	int			left;
	int			right;
	int			turn_left;
	int			turn_right;
}				t_move;

typedef struct	s_raycast
{
	double		camerax;
	double		raydirx;
	double		raydiry;
	int			mapx;
	int			mapy;
	double		sidedistx;
	double		sidedisty;
	double		deltadistx;
	double		deltadisty;
	double		perpwalldist;
	int			stepx;
	int			stepy;
	int			hit;
	int			side;
	int			lineheight;
	int			drawstart;
	int			drawend;
}				t_raycast;

typedef struct	s_index
{
	t_image		img;
	t_cub		cub;
	t_move		move;
	t_raycast	ray;
}				t_index;

int				quit(t_cub *cub);
void			ft_error(int error);
void			ft_free_matrice(char **str);
void			ft_parse(t_cub *cub, char *path);
int				get_color(char *str);
int				raycast(t_index *m);
void			go_up_down(t_cub *cub, int direction);
void			go_left_right(t_cub *cub, int direction);
void			go_turn_left_right(t_cub *cub, int direction);
void			check_map(t_cub *cub);
int				ft_move(t_index *m);
int				ft_release(int keycode, t_move *move);
int				ft_press(int keycode, t_move *move);

#endif

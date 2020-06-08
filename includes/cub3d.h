/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 11:47:59 by nsimon            #+#    #+#             */
/*   Updated: 2020/06/06 19:22:36 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include <fcntl.h>

# include "libft.h"
# include "mlx.h"

#ifdef __APPLE__
# define ESC 53
# define FORWARD 13
# define BACK 1
# define LEFT 0
# define RIGHT 2
# define TURNLEFT 123
# define TURNRIGHT 124
# define APPLE 1
#endif

#ifdef __linux__
# define ESC 65307
# define FORWARD 122
# define BACK 115
# define LEFT 113
# define RIGHT 100
# define TURNLEFT 65361
# define TURNRIGHT 65363
# define APPLE 0
#endif

# define PRESS_EVENT 2
# define PRESS_MASK 1
# define RELEASE_EVENT 3
# define RELEASE_MASK 2
# define MOVE_SPEED 0.05
# define ROTATE_SPEED 0.02

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
	int			nbrsprt;
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
	double		wallx;
	int			texx;
	double		step;
	double		texpos;
	t_texture	*current;
	double		*zbuff;
}				t_raycast;

typedef struct	s_sprite
{
	int			x;
	int			y;
	double		distance;
}				t_sprite;

typedef struct	s_sprcalc
{
	double		spr_x;
	double		spr_y;
	double		invert;
	double		trsfm_x;
	double		trsfm_y;
	int			sprscreen_x;
	int			spr_h;
	int			drawstart_y;
	int			drawend_y;
	int 		spr_w;
	int			drawstart_x;
	int			drawend_x;
	int			strip;
	int			texx;
	int			texy;
	int			*color;
}				t_sprcalc;

typedef struct	s_index
{
	t_image		img;
	t_cub		cub;
	t_move		move;
	t_raycast	ray;
	t_sprite	*sprite;
	t_sprcalc	sprcalc;
}				t_index;

int				quit(t_index *m);
void			ft_error(int error);
void			ft_free_matrice(char **str);
void			ft_parse(t_cub *cub, char *path);
int				get_color(char *str);
int				raycast(t_index *m);
void			ft_move_init(t_index *m);
void			go_up_down(t_cub *cub, int direction);
void			go_left_right(t_cub *cub, int direction);
void			go_turn_left_right(t_cub *cub, int direction);
void			check_map(t_cub *cub);
int				color_wall(t_index *m, int i, int x, int drawEnd);
int				textures_wall(t_index *m, int i, int x, int drawEnd);
int				ft_move(t_index *m);
int				ft_release(int keycode, t_move *move);
int				ft_press(int keycode, t_move *move);
void			manage_sprite(t_index *m);
void			index_sprite(t_index *m);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 11:47:59 by nsimon            #+#    #+#             */
/*   Updated: 2020/06/13 20:08:14 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>

# include "libftprintf.h"
# include "mlx.h"

# ifdef __APPLE__
#  define ESC 53
#  define FORWARD 13
#  define BACK 1
#  define LEFT 0
#  define RIGHT 2
#  define TURNLEFT 123
#  define TURNRIGHT 124
#  define SPRINT 257
#  define APPLE 1
#  define LINUX 0
# endif

# ifdef __linux__
#  define ESC 65307
#  define FORWARD 122
#  define BACK 115
#  define LEFT 113
#  define RIGHT 100
#  define TURNLEFT 65361
#  define TURNRIGHT 65363
#  define SPRINT 65505
#  define APPLE 0
#  define LINUX 1
# endif

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
	int			nbrsprt;
	int			save;
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
	float		movespeed;
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
	int			spr_w;
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
void			ft_free_matrice(char **str);
void			ft_parse(t_cub *cub, char *path);
void			ft_error(int error);
void			check_parse_error(t_cub *cub);
int				get_color(char *str);
int				raycast(t_index *m);
int				check_textures(char *str);
void			ft_move_init(t_index *m);
void			go_up_down(t_index *m, int direction);
void			go_left_right(t_index *m, int direction);
void			go_turn_left_right(t_cub *cub, int direction);
int				check_map(t_cub *cub);
int				textures_wall(t_index *m, int i, int x, int drawend);
int				ft_move(t_index *m);
int				ft_release(int keycode, t_move *move);
int				ft_press(int keycode, t_move *move);
void			manage_sprite(t_index *m);
void			index_sprite(t_index *m);
void			screen_shot(t_index *m);
void			init_cub(t_index *m);
void			write_img(t_index *m, int drawstart, int drawend, int x);
void			init_sprite(t_index *m, int i);
void			ft_free_matrice(char **str);
void			check_color(char *str, t_color *rvb);
int				verif_size(char *str);
void			calc_dir(t_cub *cub, char c);
void			get_pose(char **map, t_cub *cub);
void			get_sprite(char **map, t_cub *cub);

#endif

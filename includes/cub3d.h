/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 11:47:59 by nsimon            #+#    #+#             */
/*   Updated: 2020/05/25 17:16:50 by nsimon           ###   ########.fr       */
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
	t_tex		*spr;
	char		**map;
	int			sol;
	int			plafond;
	t_coord_dbl	pos;
	t_coord_dbl	plane;
	t_coord_dbl	dir;
}				t_cub;

typedef struct	s_image
{
	void	*img;
	int		*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_image;

typedef struct	s_move
{
	int			esc;
	int			foward;
	int			back;
	int			left;
	int			right;
	int			turn_left;
	int			turn_right;
	int			sprint;
	int			texture;
}				t_move;

typedef struct s_raycast
{
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int		mapX;
	int		mapY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
	int		stepX;
	int		stepY;
	int		hit;
	int		side;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
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
void			put_color(int color, t_cub *cub);
int				ft_actual(t_cub *cub);
int				get_color(char *str);
int				raycast(t_index *m);
void			go_up_down(t_cub *cub, int direction);
void			go_left_right(t_cub *cub, int direction);
void			go_turn_left_right(t_cub *cub, int direction);
void 			check_map(t_cub *cub);
int				ft_move(t_index *m);
int				ft_release(int keycode, t_move *move);
int				ft_press(int keycode, t_move *move);

#endif

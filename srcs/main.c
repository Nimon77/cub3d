/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 11:21:10 by nsimon            #+#    #+#             */
/*   Updated: 2020/06/04 17:50:24 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

int	init(t_index *m, char *arg)
{
	if ((m->cub.m_ptr = mlx_init()) == NULL)
		return (EXIT_FAILURE);
	m->cub.win.w = 0;
	m->cub.win.h = 0;
	m->cub.map = malloc(sizeof(m->cub.map));
	m->cub.map[0] = ft_strdup("");
	m->cub.pos.x = -1;
	m->cub.pos.y = -1;
	m->cub.dir.x = -1;
	m->cub.dir.y = 0;
	m->cub.plane.x = 0;
	m->cub.plane.y = 0.66;
	ft_move_init(m);
	ft_parse(&m->cub, arg);
	m->img.img = mlx_new_image(m->cub.m_ptr, m->cub.win.w, m->cub.win.h);
	m->img.addr = (int *)mlx_get_data_addr(m->img.img, &m->img.bits_per_pixel,
										   &m->img.line_length, &m->img.endian);
	m->img.line_length /= 4;
	if ((m->ray.zbuff = malloc(sizeof(*m->ray.zbuff) * m->cub.win.w)) == 0)
		ft_error(99);
	if ((m->sprite = malloc(sizeof(*m->sprite) * m->cub.nbrsprt)) == NULL)
		ft_error(99);
	index_sprite(m);
	return (0);
}

int	loop(t_index *m)
{
	raycast(m);
	ft_move(m);
	mlx_put_image_to_window(m->cub.m_ptr, m->cub.m_win, m->img.img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_index	m;
	
	if (argc > 1)
	{
		if (init(&m, argv[1]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		m.cub.m_win = mlx_new_window(m.cub.m_ptr, m.cub.win.w, m.cub.win.h,
				"Cub3D");
		mlx_do_key_autorepeaton(m.cub.m_ptr);
		mlx_hook(m.cub.m_win, PRESS_EVENT, PRESS_MASK, ft_press, &m.move);
		mlx_hook(m.cub.m_win, RELEASE_EVENT, RELEASE_MASK, ft_release, &m.move);
		mlx_hook(m.cub.m_win, 17, 0, &quit, &m.cub);
		mlx_loop_hook(m.cub.m_ptr, &loop, &m);
		mlx_loop(m.cub.m_ptr);
		quit(&m);
	}
}

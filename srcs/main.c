/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 11:21:10 by nsimon            #+#    #+#             */
/*   Updated: 2020/06/13 19:32:42 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_param(char **argv, int argc)
{
	if (argc >= 2)
		ft_memcmp(argv[1], "--help", 6) == 0 ||
		ft_memcmp(argv[1], "-h", 2) == 0 ? ft_error(97) : 0;
	if (argc == 3)
		ft_memcmp(argv[2], "--help", 6) == 0 ||
		ft_memcmp(argv[2], "-h", 2) == 0 ? ft_error(97) : 0;
	ft_strnstr(&argv[1][ft_strlen(argv[1]) - 4], ".cub", 4) == NULL ?
			ft_error(96) : 0;
	if (argc == 3)
		ft_memcmp(argv[2], "--save", 6) != 0 ? ft_error(98) : 0;
}

void	init(t_index *m, char *arg)
{
	init_cub(m);
	m->move.movespeed = 0;
	ft_move_init(m);
	ft_parse(&m->cub, arg);
	check_parse_error(&m->cub);
	if ((m->ray.zbuff = malloc(sizeof(*m->ray.zbuff) * m->cub.win.w)) == NULL)
		ft_error(99);
	if ((m->sprite = malloc(sizeof(*m->sprite) * m->cub.nbrsprt)) == NULL)
		ft_error(99);
	index_sprite(m);
}

int		loop(t_index *m)
{
	m->img.img = mlx_new_image(m->cub.m_ptr, m->cub.win.w, m->cub.win.h);
	m->img.addr = (int *)mlx_get_data_addr(m->img.img, &m->img.bits_per_pixel,
										&m->img.line_length, &m->img.endian);
	m->img.line_length /= 4;
	raycast(m);
	m->cub.save ? screen_shot(m) : 0;
	ft_move(m);
	mlx_put_image_to_window(m->cub.m_ptr, m->cub.m_win, m->img.img, 0, 0);
	mlx_destroy_image(m->cub.m_ptr, m->img.img);
	return (0);
}

int		main(int argc, char **argv)
{
	t_index	m;

	check_param(argv, argc);
	if (argc > 1 && argc <= 3)
	{
		init(&m, argv[1]);
		if (argc == 3)
			if (ft_memcmp(argv[2], "--save", 6) == 0)
			{
				m.cub.save = 1;
				loop(&m);
			}
		m.cub.m_win = mlx_new_window(m.cub.m_ptr, m.cub.win.w, m.cub.win.h,
				"Cub3D");
		mlx_do_key_autorepeaton(m.cub.m_ptr);
		mlx_hook(m.cub.m_win, PRESS_EVENT, PRESS_MASK, ft_press, &m.move);
		mlx_hook(m.cub.m_win, RELEASE_EVENT, RELEASE_MASK, ft_release, &m.move);
		mlx_hook(m.cub.m_win, 17, 0, &quit, &m);
		mlx_loop_hook(m.cub.m_ptr, &loop, &m);
		mlx_loop(m.cub.m_ptr);
	}
	ft_error(98);
}

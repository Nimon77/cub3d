/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 17:45:34 by nsimon            #+#    #+#             */
/*   Updated: 2020/05/29 17:45:34 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_move_init(t_index *m)
{
	m->move.esc = 0;
	m->move.left = 0;
	m->move.turn_left = 0;
	m->move.right = 0;
	m->move.turn_right = 0;
	m->move.back = 0;
	m->move.foward = 0;
}
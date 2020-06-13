/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 14:08:54 by nsimon            #+#    #+#             */
/*   Updated: 2020/06/13 17:53:28 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	write_header(int fd, t_index *m, int tmp, int file_size)
{
	char	header[54];
	
	ft_bzero(header, 54);
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	header[2] = (unsigned char)(file_size);
	header[3] = (unsigned char)(file_size >> 8);
	header[4] = (unsigned char)(file_size >> 16);
	header[5] = (unsigned char)(file_size >> 24);
	header[10] = (unsigned char)(54);
	header[14] = (unsigned char)(40);
	header[18] = (unsigned char)(tmp);
	header[19] = (unsigned char)(tmp >> 8);
	header[20] = (unsigned char)(tmp >> 16);
	header[21] = (unsigned char)(tmp >> 24);
	tmp = -m->cub.win.h;
	header[22] = (unsigned char)(tmp);
	header[23] = (unsigned char)(tmp >> 8);
	header[24] = (unsigned char)(tmp >> 16);
	header[25] = (unsigned char)(tmp >> 24);
	header[26] = (unsigned char)(1);
	header[28] = (unsigned char)(32);
	write(fd, header, 54);
}

void	write_data(int fd, t_index *m)
{
	char 	*tmp;
	int		i;
	
	i = 0;
	tmp = (char *)m->img.addr;
	while (i < m->cub.win.h)
		write(fd, &tmp[i++ * (m->img.line_length * 4)], m->cub.win.w * 4);
}

void	screen_shot(t_index *m)
{
	int	fd;
	int	tmp;
	int	file_size;
	
	if ((fd = open("screenshot.bmp", O_CREAT | O_RDWR, S_IRWXU)) < 0)
		quit(m);
	tmp = m->cub.win.w;
	file_size = 14 + 40 + (m->cub.win.w * m->cub.win.h) * 4;
	write_header(fd, m, tmp, file_size);
	write_data(fd, m);
	close(fd);
	quit(m);
}

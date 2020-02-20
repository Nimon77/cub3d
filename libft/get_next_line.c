/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 13:09:46 by nsimon            #+#    #+#             */
/*   Updated: 2020/01/24 14:08:20 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		error_check(int fd, char **stat, char **line, char **buff)
{
	if (read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0 || !line)
	{
		free(*stat);
		return (1);
	}
	if (!(*buff = malloc(sizeof(**buff) * (BUFFER_SIZE + 1))))
		return (1);
	return (0);
}

int		has_nl(const char *str)
{
	int i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*get_line(char *stat)
{
	char	*new_line;
	int		i;

	if (!(stat))
		return (ft_strdup(""));
	i = 0;
	while (stat[i] && stat[i] != '\n')
		i++;
	if (stat[i] == '\n')
		new_line = ft_substr(stat, 0, i);
	else
		new_line = ft_strdup(stat);
	return (new_line);
}

char	*get_new_stat(char *stat)
{
	int		i;

	if (!(stat))
		return (NULL);
	i = 0;
	while (stat[i] && stat[i] != '\n')
		i++;
	if (stat[i] == '\n')
	{
		if (stat[i + 1])
			return (ft_substr(stat, i + 1, ft_strlen(stat) - (i + 1)));
		else
			return (ft_strdup(""));
	}
	return (NULL);
}

int		get_next_line(int fd, char **line)
{
	static char	*stat;
	char		*tmp;
	char		*buff;
	int			res;

	if (error_check(fd, &stat, line, &buff))
		return (-1);
	res = 1;
	while (!has_nl(stat) && res > 0)
	{
		ft_bzero(buff, BUFFER_SIZE + 1);
		res = read(fd, buff, BUFFER_SIZE);
		tmp = stat;
		stat = ft_strjoin(stat, buff);
		ft_bzero(buff, BUFFER_SIZE + 1);
		free(tmp);
	}
	*line = get_line(stat);
	tmp = stat;
	stat = get_new_stat(stat);
	free(tmp);
	free(buff);
	if (res <= 0)
		return (res);
	return (1);
}

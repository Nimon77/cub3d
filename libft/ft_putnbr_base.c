/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 18:02:23 by nsimon            #+#    #+#             */
/*   Updated: 2020/02/21 22:16:26 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_reverse(char *conv)
{
	int		i;
	int		size;
	char	*tmp;
	
	size = (int)ft_strlen(conv) - 1;
	i = 0;
	if (!(tmp = (char *)malloc(sizeof(tmp) * size + 1)))
		return (NULL);
	while (size >= 0)
		tmp[i++] = conv[size--];
	tmp[i] = '\0';
	free(conv);
	return (tmp);
}

static int		convert_base(unsigned int nbr, char *base, char *value)
{
	int		i;
	int		baselen;
	int		tmp;
	
	i = 0;
	baselen = ft_strlen(base);
	while (nbr != 0)
	{
		tmp = nbr % baselen;
		value[i] = base[tmp];
		nbr /= baselen;
		i++;
	}
	return (i);
}

static int		check_base(char *str)
{
	int		i;
	int		j;
	
	i = 0;
	if (ft_strlen(str) < 2)
		return (0);
	while (str[i] != '\0')
	{
		j = i + 1;
		if (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' ||
			str[i] == '\f' || str[i] == '\r' || str[i] == '+' ||
			str[i] == '-')
			return (0);
		while (str[j] != '\0')
		{
			if (str[i] == str[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

char	*ft_itoa_base(int nbr, char *base)
{
	int		i;
	char	value[34];
	char	neg;
	
	i = 0;
	if (check_base(base))
	{
		neg = '\0';
		if (nbr < 0)
		{
			neg = '-';
			i = convert_base((nbr * -1), base, value);
		}
		else if (nbr == 0)
			value[i++] = base[0];
		else
		{
			i = convert_base(nbr, base, value);
		}
		value[i] = neg;
	}
	else
		value[i] = '0';
	value[i + 1] = '\0';
	return (ft_reverse(value));
}
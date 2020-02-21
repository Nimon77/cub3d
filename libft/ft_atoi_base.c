/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 23:24:35 by nsimon            #+#    #+#             */
/*   Updated: 2020/02/21 22:07:13 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int		ft_strstr(char *str, char to_find)
{
	int		i;
	
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == to_find)
			return (i);
		i++;
	}
	return (-1);
}

static int		is_spec_print(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' ||
		c == ' ')
		return (1);
	return (0);
}

static void	str_neg(int *neg)
{
	if (*neg == -1)
		*neg = 1;
	else
		*neg = -1;
}

static int		check_base(char *str, int baselen)
{
	int		i;
	int		j;
	
	i = 0;
	if (baselen < 2)
		return (0);
	while (str[i] != '\0')
	{
		j = i + 1;
		if (str[i] < '!' || str[i] == '%' || (str[i] >= '(' && str[i] <= '/') ||
			(str[i] >= '<' && str[i] <= '>') || str[i] == '@' ||
			str[i] > '~')
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

int		ft_atoi_base(char *str, char *base)
{
	int i;
	int value;
	int baselen;
	int neg;
	
	i = 0;
	value = 0;
	baselen = 0;
	neg = 1;
	while (base[i++] != '\0')
		baselen += 1;
	if (check_base(base, baselen))
	{
		i = 0;
		while (is_spec_print(str[i]) && str[i] != '\0')
			i++;
		while ((str[i] == '-' || str[i] == '+') && str[i] != '\0')
			if (str[i++] == '-')
				str_neg(&neg);
		while (str[i] != '\0' && ft_strstr(base, str[i]) != -1)
			value = (value * baselen) + ft_strstr(base, str[i++]);
		value = (value * neg);
	}
	return (value);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_l_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcrosnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/13 12:17:14 by pcrosnie          #+#    #+#             */
/*   Updated: 2016/02/15 16:08:23 by pcrosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*ft_set_month(long nb)
{
	if (nb <= 31)
		return ("Jan ");
	if (nb <= 60)
		return ("Feb ");
	if (nb <= 91)
		return ("Mar ");
	if (nb <= 121)
		return ("Apr ");
	if (nb <= 152)
		return ("May ");
	if (nb <= 182)
		return ("Jun ");
	if (nb <= 213)
		return ("Jul ");
	if (nb <= 243)
		return ("Aug ");
	if (nb <= 274)
		return ("Sep ");
	if (nb <= 304)
		return ("Oct ");
	if (nb <= 335)
		return ("Nov ");
	if (nb <= 365)
		return ("Dec ");
	return (0);
}

int		ft_set_nb(long nb)
{
	if (nb <= 31)
		return (nb);
	if (nb <= 60)
		return (nb - 30);
	if (nb <= 91)
		return (nb - 59);
	if (nb <= 121)
		return (nb - 90);
	if (nb <= 152)
		return (nb - 120);
	if (nb <= 182)
		return (nb - 151);
	if (nb <= 213)
		return (nb - 181);
	if (nb <= 243)
		return (nb - 212);
	if (nb <= 274)
		return (nb - 242);
	if (nb <= 304)
		return (nb - 273);
	if (nb <= 335)
		return (nb - 303);
	if (nb <= 365)
		return (nb - 334);
	return (0);
}

char	*ft_set_hour(int rest)
{
	char *str;
	char *tmp;
	int	nb;

	nb = rest % 3600;
	rest = (rest / 3600) + 1;
	nb = nb / 60;
	if (rest > 9)
		str = ft_itoa(rest);
	else
	{
		str = (char *)malloc(sizeof(char) * 2);
		str[0] = '0';
		str[1] = rest + 48;
	}
	str[ft_strlen(str)] = ':';
	if (nb > 9)
		str = ft_strjoin(str, ft_itoa(nb));
	else
	{
		tmp = (char *)malloc(sizeof(char) * 2);
		tmp[0] = '0';
		tmp[1] = nb + 48;
		str = ft_strjoin(str, tmp);
		free(tmp);
	}
	return (str);
}

char	*ft_set_date(long nb, int rest)
{
	char *str = NULL;
		str = ft_set_month(nb);
		nb = ft_set_nb(nb);
		if (nb < 10)
			str = ft_strjoin(str, " ");
		str = ft_strjoin(str, ft_itoa(nb));
		str[ft_strlen(str)] = ' ';
		str = ft_strjoin(str, ft_set_hour(rest));
		return (str);
}

t_file	*ft_retrieves_date(t_file *begin)
{
	long nb;
	int i;
//	int rest;
	t_file *ptr;

	ptr = begin;
	while (ptr->next != NULL)
	{
		i = -2;
		nb = ptr->info->st_time;
/*		rest = nb % (3600 * 24);
		nb = nb / (3600 * 24);
		while (nb > 365)
		{
			if (i % 4 == 0)
				nb = nb - 366;
			else
				nb = nb - 365;
			i++;
		}*/
		ptr->date = ft_strsub(ctime(&nb), 4, 12);
		ft_putstr(ptr->date);
		ft_putchar(' ');
		ft_putstr(ptr->name);
		ft_putchar('\n');
		ptr = ptr->next;
	}
	return (begin);
}

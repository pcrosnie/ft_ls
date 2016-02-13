/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_l_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcrosnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/13 12:17:14 by pcrosnie          #+#    #+#             */
/*   Updated: 2016/02/13 19:21:10 by pcrosnie         ###   ########.fr       */
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
	int	nb;

	nb = rest % 3600;
	rest = (rest / 3600) + 1;
	nb = nb / 60;
	str = ft_itoa(rest);
	str[ft_strlen(str)] = ':';
	str = ft_strjoin(str, ft_itoa(nb));
	return (str);
}



char	*ft_set_date(long nb, int rest)
{
//	char *tmp;
	char *str = NULL;
		str = ft_set_month(nb);
		nb = ft_set_nb(nb);
		str = ft_strjoin(str, ft_itoa(nb));
		str[ft_strlen(str)] = ' ';
		str = ft_strjoin(str, ft_set_hour(rest));
//		ft_putchar('\n');
//		ft_putstr(str);
//		ft_putchar('\n');
		return (str);
}

t_file	*ft_retrieves_date(t_file *begin)
{
	long nb;
	int i;
	int rest;
	t_file *ptr;

	ptr = begin;
	while (ptr != NULL)
	{
		i = -2;
		nb = ptr->info->st_mtimespec.tv_sec;
		rest = nb % (3600 * 24);
		nb = nb / (3600 * 24);
		while (nb > 365)
		{
			if (i % 4 == 0)
				nb = nb - 366;
			else
				nb = nb - 365;
			i++;
		}
		ptr->date = ft_set_date(nb, rest);
		ft_putstr(ptr->date);
		ft_putchar('\n');
		ft_putstr(ptr->name);
		ft_putchar('\n');
		ft_putnbr(nb);
		ft_putchar('\n');
		ft_putnbr(rest);
		ft_putchar('\n');
		ptr = ptr->next;
	}
	return (begin);
}

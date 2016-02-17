/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_l_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcrosnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/13 12:17:14 by pcrosnie          #+#    #+#             */
/*   Updated: 2016/02/17 12:07:00 by pcrosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_set_max_bytes_size(t_file *begin)
{
	t_file *ptr;
	size_t nb;

	nb = 0;
	ptr = begin;
	while (ptr->next != NULL)
	{
		if (ft_strlen(ft_itoa(ptr->info->st_size)) > nb)
			nb = ft_strlen(ft_itoa(ptr->info->st_size));
		ptr = ptr->next;
	}
	ptr = begin;
	while (ptr->next != NULL)
	{
		ptr->max_bytes_size = nb;
		ptr = ptr->next;
	}
}

void	ft_set_rights(t_file *begin)
{
	t_file *ptr;
	mode_t val;

	ptr = begin;
	(S_ISCHR(ptr->info->st_mode)) ? ft_putchar('c') : 0;
	(S_ISLNK(ptr->info->st_mode)) ? ft_putchar('l') : 0;
	(S_ISDIR(ptr->info->st_mode)) ? ft_putchar('d') : 0;
	(S_ISREG(ptr->info->st_mode)) ? ft_putchar('-') : 0;
	(S_ISFIFO(ptr->info->st_mode)) ? ft_putchar('p') : 0;
	(S_ISBLK(ptr->info->st_mode)) ? ft_putchar('b') : 0;
	(S_ISSOCK(ptr->info->st_mode)) ? ft_putchar('s') : 0;
	val = (ptr->info->st_mode & ~S_IFMT);
	(val & S_IRUSR) ? ft_putchar('r') : ft_putchar('-');
	(val & S_IWUSR) ? ft_putchar('w') : ft_putchar('-');
	(val & S_IXUSR) ? ft_putchar('x') : ft_putchar('-');
	(val & S_IRGRP) ? ft_putchar('r') : ft_putchar('-');
	(val & S_IWGRP) ? ft_putchar('w') : ft_putchar('-');
	(val & S_IXGRP) ? ft_putchar('x') : ft_putchar('-');
	(val & S_IROTH) ? ft_putchar('r') : ft_putchar('-');
	(val & S_IWOTH) ? ft_putchar('w') : ft_putchar('-');
	(val & S_IXOTH) ? ft_putchar('x') : ft_putchar('-');
	ft_putstr("  ");
}

void	ft_l_display(t_file *begin)
{
	t_file *ptr;
	int i;
	int tmp;

	i = 0;
	ptr = begin;
	ft_set_max_bytes_size(begin);
	while (ptr->next != NULL)
	{
		tmp = ft_strlen(ft_itoa(ptr->info->st_size));
		i = 0;
		ft_set_rights(ptr);
		ft_putstr(ptr->hard_links);
		ft_putstr(ptr->usr_name);
		ft_putstr(ptr->group_name);
		ft_putchar(' ');
		while (i <= ptr->max_bytes_size - tmp)
		{
			ft_putchar(' ');
			i++;
		}
		ft_putnbr(ptr->info->st_size);
		ft_putchar(' ');
		ft_putstr(ptr->date);
		ft_putchar(' ');
		ft_putstr(ptr->name);
		ft_putchar('\n');
		ptr = ptr->next;
	}
}

t_file	*ft_retrieves_date(t_file *begin)
{
	long nb;
	int i;
	t_file *ptr;

	ptr = begin;
	while (ptr->next != NULL)
	{
		i = -2;
		nb = ptr->info->st_time;
		ptr->date = ft_strsub(ctime(&nb), 4, 12);
		ptr = ptr->next;
	}
	return (begin);
}

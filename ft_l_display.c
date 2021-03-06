/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_l_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcrosnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/13 12:17:14 by pcrosnie          #+#    #+#             */
/*   Updated: 2016/03/08 11:07:09 by pcrosnie         ###   ########.fr       */
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
	(S_ISLNK(ptr->info->st_mode)) ? ft_putchar('l') : 0;
	(S_ISCHR(ptr->info->st_mode)) ? ft_putchar('c') : 0;
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

void	ft_get_min_max(t_file *begin)
{
	t_file *ptr;
	int tmp;
	int max;

	ptr = begin;
	ptr->min_max = 0;
	max = 0;
	while (ptr->next != NULL)
	{
		tmp = ft_strlen(ft_itoa(minor(ptr->info->st_rdev)));
		if (tmp > max)
			max = tmp;
		ptr = ptr->next;
	}
	ptr = begin;
	while (ptr->next != NULL)
	{
		ptr->min_max = max;
		ptr = ptr->next;
	}
}

void	ft_get_maj_max(t_file *begin)
{
	t_file *ptr;
	int tmp;
	int max;

	ptr = begin;
	ptr->maj_max = 0;
	max = 0;
	while (ptr->next != NULL)
	{
		tmp = ft_strlen(ft_itoa(major(ptr->info->st_rdev)));
		if (tmp > max)
			max = tmp;
		ptr = ptr->next;
	}
	ptr = begin;
	while (ptr->next != NULL)
	{
		ptr->maj_max = max;
		ptr = ptr->next;
	}
}

void	ft_set_min_maj(t_file *ptr)
{
	char *str;
	char *str2;
	int i;

	i = 0;
	str = ft_itoa(major(ptr->info->st_rdev));
	str2 = ft_itoa(minor(ptr->info->st_rdev));
	while (ft_strlen(str) + i <= ptr->min_max)
	{
		ft_putchar(' ');
		i++;
	}
	ft_putstr(str);
	ft_putchar(',');
	i = 0;
	while (ft_strlen(str2) + i <= ptr->maj_max)
	{
		ft_putchar(' ');
		i++;
	}
	ft_putchar(' ');
	ft_putstr(str2);
	while (ptr->prev != NULL)
		ptr = ptr->prev;
	while (ptr->next != NULL)
	{
		ptr->max_bytes_size = ptr->min_max + ptr->maj_max + 3;
		ptr = ptr->next;
	}
}

void	ft_link_display(t_file *ptr)
{
	char *buf;
	int ret;

	buf = (char *)malloc(sizeof(char) * 1000);
	(ptr->path[ft_strlen(ptr->path)] != '/') ? ptr->path[ft_strlen(ptr->path)] = '/' : 0;
	ret = readlink(ft_strjoin(ptr->path, ptr->name), buf, 1000);
	buf[ret] = '\0';
	ft_putstr(" -> ");
	ft_putstr(buf);
}

void	ft_display_elem(t_file *ptr)
{
	int 	tmp;
	int		i;

	tmp = ft_strlen(ft_itoa(ptr->info->st_size));
	i = 0;
	ft_set_rights(ptr);
	ft_putstr(ptr->hard_links);
	ft_putstr(ptr->usr_name);
	ft_putstr(ptr->group_name);
	ft_putchar(' ');
	if (S_ISCHR(ptr->info->st_mode) != 0 || S_ISBLK(ptr->info->st_mode) != 0)
		ft_set_min_maj(ptr);
	else
	{
		while (i <= ptr->max_bytes_size - tmp)
		{
			ft_putchar(' ');
			i++;
		}
		ft_putnbr(ptr->info->st_size);
	}
	ft_putchar(' ');
	ft_putstr(ptr->date);
	ft_putchar(' ');
	ft_putstr(ptr->name);
	if (S_ISLNK(ptr->info->st_mode))
		ft_link_display(ptr);
	ft_putchar('\n');
}

int		ft_retrieves_total_blksize(t_file *begin, int option)
{
	t_file *ptr;
	int nb;

	ptr = begin;
	nb = 0;
	while (ptr->next != NULL)
	{
		if (option == 0)
		{
			while (ptr->next != NULL && ptr->name[0] == '.')
				ptr = ptr->next;
		}
		nb += ptr->info->st_blocks;
		if (ptr->next != NULL)
		ptr = ptr->next;
		ft_putchar('E');
	}
	return (nb);
}

void	ft_set_min_maj_max(t_file *begin)
{
	t_file *ptr;
	int nb2;
	int nb;

	ptr = begin;
	ptr->min_max = 0;
	ptr->maj_max = 0;
	nb = 0;
	nb2 = 0;
	while (ptr->next != NULL)
	{
		if (major(ptr->info->st_dev) > nb)
			nb = major(ptr->info->st_dev);
		if (minor(ptr->info->st_dev) > nb2)
			nb2 = minor(ptr->info->st_dev);
		ptr = ptr->next;
	}
	ptr = begin;
	while (ptr->next != NULL)
	{
		ptr->min_max = nb2;
		ptr->maj_max = nb;
		ptr = ptr->next;
	}
}

void	ft_l_display(t_file *begin, int *options)
{
	t_file *ptr;
	int i;

	i = 0;
	ptr = begin;
	ft_set_max_bytes_size(begin);
	ft_putstr("total ");
	ft_putnbr(ft_retrieves_total_blksize(begin, options[1]));
	ft_putchar('\n');
	while (ptr->next != NULL)
	{
		if (options[1] == 0)
		{
			while (ptr->next != NULL && ptr->name[0] == '.')
				ptr = ptr->next;
		}
		if (options[2] == 0)
			ft_display_elem(ptr);
		ptr = ptr->next;
	}
	ptr = ptr->prev;
	if (options[2] == 1)
	{
		while (ptr != NULL)
		{
			if (options[1] == 0)
			{
				while (ptr != NULL && ptr->name[0] == '.')
					ptr = ptr->prev;
			}
			if (ptr)
			{
				ft_display_elem(ptr);
				ptr = ptr->prev;
			}
		}
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

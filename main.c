/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcrosnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 12:22:44 by pcrosnie          #+#    #+#             */
/*   Updated: 2016/03/03 11:18:51 by pcrosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_print_list(t_file *ptr, int a, int b)
{
	while (ptr->next != NULL)
	{
		if (a == 0)
		{
			while (ptr->next != NULL && ptr->name[0] == '.')
				ptr = ptr->next;
		}
		if (b != 1)
		{
			ft_putstr(ptr->name);
			ft_putchar('\n');
		}
		ptr = ptr->next;
	}
	ptr = ptr->prev;
	if (b == 1)
	{
		while (ptr != NULL)
		{
			if (a == 0)
			{
				while (ptr != NULL && ptr->name[0] == '.')
					ptr = ptr->prev;
			}
			if (ptr)
			{
			ft_putstr(ptr->name);
			ft_putchar('\n');
			ptr = ptr->prev;
			}
		}
	}
}

t_file	*ft_l_option(char *path, t_file *begin, DIR *dir, int *options)
{
	begin = ft_retrieve(dir, begin, path);
	begin = ft_sort_lex(begin);
	begin = ft_retrieves_date(begin);
	ft_get_min_max(begin);
	ft_get_maj_max(begin);
	ft_retrieves_usr_gr_id(begin);
	ft_retrieves_hardlinks(begin);
	ft_l_display(begin, options);
	return (begin);
}

void	ft_no_arg(DIR *dir, t_file *begin)
{
	dir = opendir(".");
	if (!dir)
		ft_error(".");
	begin = ft_retrieve(dir, begin, ".");
	begin = ft_sort_lex(begin);
	ft_print_list(begin, 0, 0);
}

void	ft_error(char *str)
{
	ft_putstr("ls: ");
	ft_putstr(str);
	ft_putstr(": ");
	ft_putstr(ft_strjoin(strerror(errno), "\n"));
	exit(0);
}

int		main(int argc, char **argv)
{
	DIR		*dir;
	t_file *begin;

	dir = NULL;
	begin = NULL;
	if (argc == 1)
		ft_no_arg(dir, begin);
	else
	{
		ft_set_options(dir, begin, argv, argc);
	}
	return (0);
}

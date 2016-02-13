/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcrosnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 12:22:44 by pcrosnie          #+#    #+#             */
/*   Updated: 2016/02/13 15:58:29 by pcrosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_print_list(t_file *ptr)
{
	while (ptr->next != NULL)
	{
		ft_putstr(ptr->name);
		ft_putchar('\n');
		ft_putnbr(ptr->info->st_ino);
		ft_putchar('\n');
		ft_putnbr(ptr->info->st_mtimespec.tv_sec);
		ft_putchar('\n');
		ptr = ptr->next;
	}
}

int		main(int argc, char **argv)
{
	DIR		*dir;
	t_file *begin;

	begin = NULL;
	if (argc == 2)
	{
		dir = opendir(argv[1]);
		begin = ft_retrieve(dir, begin);
		begin = ft_sort_lex(begin);
		begin = ft_retrieves_date(begin);
//		begin = ft_l_display(begin, argv[1]);
//		ft_print_list(begin);
	}
	return (0);
}

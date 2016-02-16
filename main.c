/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcrosnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 12:22:44 by pcrosnie          #+#    #+#             */
/*   Updated: 2016/02/16 15:54:16 by pcrosnie         ###   ########.fr       */
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
		ft_putnbr(ptr->info->st_time);
		ft_putchar('\n');
		ptr = ptr->next;
	}
}

void	ft_l_option(char *path, t_file *begin, DIR *dir)
{
		begin = ft_retrieve(dir, begin, path);
		begin = ft_sort_lex(begin);
		begin = ft_retrieves_date(begin);
		ft_retrieves_usr_gr_id(begin);
		ft_retrieves_hardlinks(begin);
		ft_l_display(begin);
}

int		main(int argc, char **argv)
{
	DIR		*dir;
	t_file *begin;
	
	begin = NULL;
	if (argc == 2)
	{		
	dir = opendir(argv[1]);
	ft_l_option(argv[1], begin, dir);}
	return (0);
}

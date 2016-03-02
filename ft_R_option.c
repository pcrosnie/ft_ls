/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_R_option.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcrosnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 17:37:49 by pcrosnie          #+#    #+#             */
/*   Updated: 2016/03/02 16:46:43 by pcrosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_R_error(char *path)
{
	ft_putstr("ls: ");
	ft_putstr(path);
	ft_putstr(": ");
	ft_putstr(ft_strjoin(strerror(errno), "\n"));
}

t_file	*ft_retrieves_n_display(t_file *ptr, char *path, int *options, DIR *dir)
{
	if (!dir)
	{
		ft_R_error(path);
		return(NULL);
	}
	if (options && options[4] == 1)
		ft_l_option(path, ptr, dir, options);
	else
	{
		ptr = ft_retrieve(dir, ptr, path);
		ptr = ft_sort_lex(ptr);
//		ft_print_list(ptr, options[1], options[2]);
	}
	return (ptr);
}

void	ft_R_option(DIR *dir, t_file *ptr, char *path, int *options)
{
	dir = opendir(path);
	char *tmp_path;
	if (dir)
	{
		ptr = ft_retrieves_n_display(ptr, path, options, dir);
		while (ptr->next != NULL)
		{
			if (S_ISDIR(ptr->info->st_mode))
			{
				tmp_path = ft_strdup(path);
				tmp_path = ft_strjoin(tmp_path, "/");
				tmp_path = ft_strjoin(tmp_path, ptr->name);
				ft_putstr(tmp_path);
				ft_putchar('\n');
				ft_R_option(dir, ptr, tmp_path, options);
				free(tmp_path);
			}
			ptr = ptr->next;
		}
	}
}








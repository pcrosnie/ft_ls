/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_R_option.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcrosnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 17:37:49 by pcrosnie          #+#    #+#             */
/*   Updated: 2016/03/08 11:16:56 by pcrosnie         ###   ########.fr       */
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
	{
		ptr = ft_l_option(path, ptr, dir, options);
	}
	else
	{
		ptr = ft_retrieve(dir, ptr, path);
		ptr = ft_sort_lex(ptr);
		ft_print_list(ptr, options[1], options[2]);
	}
	return (ptr);
}

void	ft_del_list(t_file **begin, int *options)
{
	t_file *ptr;

	ptr = *begin;
	while (ptr->next->next != NULL)
	{
		if (options[4] == 1)
		{
		ft_putstr("DATE\n");
		free(ptr->date);
		ft_putstr("NAME\n");
		free(ptr->group_name);
		ft_putstr("GROUP\n");
		free(ptr->usr_name);
		ft_putstr("LINKS\n");
		free(ptr->hard_links);
		ft_putstr("INFO\n");
		free(ptr->info);
		}
		ptr = ptr->next;
	}
}

char	*ft_set_path(char *path, t_file *ptr)
{
	char *tmp_path;

	tmp_path = ft_strdup(path);
	tmp_path = ft_strjoin(tmp_path, "/");
	tmp_path = ft_strjoin(tmp_path, ptr->name);
	return (tmp_path);
}
/*
void	ft_R_option(char *path, int *options)
{
	DIR *dir;
	t_file *ptr;
	char *tmp_path;

	tmp_path = ft_strdup(path);
	while ((dir = opendir(tmp_path)))
	{
		ptr = ft_retrieves_n_display(ptr, path, options, dir);
		closedir(dir);
*/		


void	ft_R_option(char *path, int *options)
{
	DIR *dir;
	t_file *ptr = NULL;
	t_file *tmp_ptr;
	char *tmp_path;
	
	dir = opendir(path);
	if (dir)
	{
		ptr = ft_retrieves_n_display(ptr, path, options, dir);
		tmp_ptr = ptr;
		ft_del_list(&tmp_ptr, options);
		closedir(dir);
		while (ptr->next != NULL)
		{
			if (S_ISDIR(ptr->info->st_mode) && ptr->name[0] != '.')
			{
				tmp_path = ft_strdup(path);
				tmp_path = ft_strjoin(tmp_path, "/");
				tmp_path = ft_strjoin(tmp_path, ptr->name);
				ft_putstr(tmp_path);
				ft_putchar('\n');
				ft_R_option(tmp_path, options);
	//			free(tmp_path);
			}
			ptr = ptr->next;
		}
//		if (tmp_path)
//		free(tmp_path);
		ft_del_list(&tmp_ptr, options);
	}
}

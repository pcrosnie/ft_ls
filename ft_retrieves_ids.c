/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_retrieves_ids.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcrosnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 12:57:36 by pcrosnie          #+#    #+#             */
/*   Updated: 2016/03/08 11:07:41 by pcrosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_set_spaces(t_file *begin, size_t *nb)
{
	t_file *ptr;

	ptr = begin;
	while (ptr->next != NULL)
	{
		while (ft_strlen(ptr->group_name) < nb[0])
		{
			ptr->group_name = ft_strjoin(ptr->group_name, " ");
		}
		while (ft_strlen(ptr->usr_name) <= nb[1] + 1)
			ptr->usr_name = ft_strjoin(ptr->usr_name, " ");
		ptr = ptr->next;
	}
}

void	ft_retrieves_usr_gr_id(t_file *begin)
{
	t_file *ptr;
	struct group *grp;
	struct passwd *usr;
	size_t *nb;

	nb = (size_t *)malloc(sizeof(size_t) * 2);
	nb[0] = 0;
	nb[1] = 0;
	ptr = begin;
	while (ptr->next != NULL)
	{
		grp = getgrgid(ptr->info->st_gid);
		ptr->group_name = ft_strdup(grp->gr_name);
		usr = getpwuid(ptr->info->st_uid);
		ptr->usr_name = ft_strdup(usr->pw_name);
		ptr = ptr->next;
	}
	ptr = begin;
	while (ptr->next != NULL)
	{
		if (ft_strlen(ptr->group_name) > nb[0])
			nb[0] = ft_strlen(ptr->group_name);
		if (ft_strlen(ptr->usr_name) > nb[1])
			nb[1] = ft_strlen(ptr->usr_name);
		ptr = ptr->next;
	}
	ft_set_spaces(begin, nb);
}

void	ft_retrieves_hardlinks(t_file *begin)
{
	t_file *ptr;
	size_t nb;

	nb = 0;
	ptr = begin;
	while (ptr->next != NULL)
	{
		if (ft_strlen(ft_itoa(ptr->info->st_nlink)) > nb)
			nb = ft_strlen(ft_itoa(ptr->info->st_nlink));
		ptr = ptr->next;
	}
	ptr = begin;
	while (ptr->next != NULL)
	{
		ptr->hard_links = ft_itoa(ptr->info->st_nlink);
		while (ft_strlen(ptr->hard_links) < nb)
			ptr->hard_links = ft_strjoin(" ", ptr->hard_links);
		ptr->hard_links = ft_strjoin(ptr->hard_links, " ");
		ptr = ptr->next;
	}
}

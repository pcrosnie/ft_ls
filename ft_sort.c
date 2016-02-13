/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcrosnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 14:04:56 by pcrosnie          #+#    #+#             */
/*   Updated: 2016/02/13 17:11:26 by pcrosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file	*ft_retrieve(DIR *dir, t_file *begin)
{
	struct dirent *file;
	t_file *adr;
	t_file *ptr;
	
	begin = (t_file *)malloc(sizeof(t_file));
	ptr = begin;
	adr = begin;
	ptr->prev = NULL;
	ptr->info = (struct stat *)malloc(sizeof(struct stat));
	while ((file = readdir(dir)))
	{
		stat(file->d_name, ptr->info);
		ptr->name = file->d_name;
		ptr->next = (t_file *)malloc(sizeof(t_file));
		ptr = ptr->next;
		ptr->prev = adr;
		adr = adr->next;
		ptr->info = (struct stat *)malloc(sizeof(struct stat));
	}
	ptr = NULL;
	return (begin);
}

void	ft_swap(t_file *ptr, t_file *ptr2)
{
	char *tmp;
	struct stat *tmp_info;

	tmp_info = ptr->info;
	tmp = ptr->name;
	ptr->name = ptr2->name;
	ptr2->name = tmp;
	ptr->info = ptr2->info;
	ptr2->info = tmp_info;
}

t_file	*ft_sort_lex(t_file *begin)
{
	t_file *ptr;
	t_file *ptr2;

	ptr = begin;
	ptr2 = ptr;
	ptr = ptr->next;
	while (ptr != NULL && ptr->name)
	{
		if (ft_strcmp(ptr2->name, ptr->name) > 0)
		{
			ft_swap(ptr2, ptr);
			ptr = begin->next;
			ptr2 = begin;
		}
		else
		{
			ptr = ptr->next;
			ptr2 = ptr2->next;
		}
	}
	return (begin);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcrosnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 14:04:56 by pcrosnie          #+#    #+#             */
/*   Updated: 2016/02/12 16:30:37 by pcrosnie         ###   ########.fr       */
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
	free(ptr->info);
	free(ptr);
	ptr = NULL;
	return (begin);
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
		if (ptr->name && ptr2->name && ft_strcmp(ptr2->name, ptr->name) < 0)
		{
			if (ptr->next)
				ptr->next->prev = ptr2;
			if (ptr2->prev)
				ptr2->prev->next = ptr;
			ptr2->next = ptr->next;
			ptr->next = ptr2;
			ptr->prev = ptr2->prev;
			ptr2->prev = ptr;
			ptr2 = begin;
			ptr = begin->next;
		}
		else
		{
			ptr = ptr->next;
			ptr2 = ptr->next;
		}
	}
	return (begin);
}

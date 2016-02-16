/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcrosnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 14:04:56 by pcrosnie          #+#    #+#             */
/*   Updated: 2016/02/16 11:29:41 by pcrosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_stat_cpy(t_info *info, struct stat *ptr)
{
	info->st_dev = ptr->st_dev;
	info->st_mode = ptr->st_mode;
	info->st_nlink = ptr->st_nlink;
	info->st_ino = ptr->st_ino;
	info->st_uid = ptr->st_uid;
	info->st_gid = ptr->st_gid;
	info->st_rdev = ptr->st_rdev;
	info->st_time = ptr->st_mtimespec.tv_sec;
	info->st_size = ptr->st_size;
	info->st_blocks = ptr->st_blocks;
	info->st_blksize = ptr->st_blksize;
	info->st_flags = ptr->st_flags;
	info->st_gen = ptr->st_gen;
}

t_file	*ft_retrieve(DIR *dir, t_file *begin, char *path)
{
	struct dirent *file;
	struct stat *tmp_info;
	t_file *adr;
	t_file *ptr;
	
	begin = (t_file *)malloc(sizeof(t_file));
	ptr = begin;
	adr = begin;
	ptr->prev = NULL;
	tmp_info = (struct stat *)malloc(sizeof(struct stat));
	ptr->info = (t_info *)malloc(sizeof(t_info));
	while ((file = readdir(dir)))
	{
		ptr->path = ft_strdup(path);
		(ptr->path[ft_strlen(ptr->path)] != '/') ? ptr->path[ft_strlen(ptr->path)] = '/' : 0;
		stat(ft_strjoin(ptr->path, file->d_name), tmp_info);
		ft_stat_cpy(ptr->info, tmp_info);
		ptr->name = ft_strdup(file->d_name);
		ptr->next = (t_file *)malloc(sizeof(t_file));
		ptr = ptr->next;
		ptr->prev = adr;
		adr = adr->next;
		ptr->info = (t_info *)malloc(sizeof(t_info));
	}
	ptr = NULL;
	return (begin);
}

void	ft_swap(t_file *ptr, t_file *ptr2)
{
	char *tmp;
	struct s_info *tmp_info;

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

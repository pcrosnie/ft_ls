/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcrosnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 12:24:20 by pcrosnie          #+#    #+#             */
/*   Updated: 2016/03/04 14:55:47 by pcrosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include <dirent.h>
# include <sys/xattr.h>
# include <sys/stat.h>
# include <time.h>
# include <grp.h>
# include <sys/types.h>
# include <errno.h>
# include <stdio.h>
# include <uuid/uuid.h>
# include <pwd.h>

typedef struct s_file
{
	char *name;
	char *date;
	char *path;
	char *group_name;
	char *usr_name;
	char *hard_links;
	int		max_bytes_size;
	size_t min_max;
	size_t  maj_max;
	struct s_info *info;
	struct s_file *next;
	struct s_file *prev;
}				t_file;

typedef struct s_info
{
	dev_t           st_dev;           /* ID of device containing file */
	mode_t          st_mode;          /* Mode of file (see below) */
	nlink_t         st_nlink;         /* Number of hard links */
	ino_t           st_ino;           /* File serial number */
	uid_t           st_uid;           /* User ID of the file */
	gid_t           st_gid;           /* Group ID of the file */
	dev_t           st_rdev;          /* Device ID */
	long			st_time;
	off_t           st_size;          /* file size, in bytes */
	blkcnt_t        st_blocks;        /* blocks allocated for file */
	blksize_t       st_blksize;       /* optimal blocksize for I/O */
	uint32_t        st_flags;         /* user defined flags for file */
	uint32_t        st_gen;
}				t_info;

int		ft_retrieves_total_blksize(t_file *begin, int options);
t_file *ft_retrieve(DIR *dir, t_file *begin, char *path);
t_file *ft_sort_lex(t_file *begin);
void	ft_l_display(t_file *begin, int *options);
t_file *ft_l_option(char *path, t_file *begin, DIR *dir, int *options);
t_file *ft_retrieves_date(t_file *begin);
void	ft_retrieves_usr_gr_id(t_file *begin);
void	ft_retrieves_hardlinks(t_file *begin);
void	ft_error(char *str);
void	ft_set_options(DIR *dir, t_file *begin, char **path, int path_size);
void	ft_print_list(t_file *ptr, int a, int b);
void	ft_get_min_max(t_file *begin);
void	ft_get_maj_max(t_file *begin);
void	ft_R_option(char *path, int *options);

#endif


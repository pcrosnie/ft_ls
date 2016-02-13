/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcrosnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 12:24:20 by pcrosnie          #+#    #+#             */
/*   Updated: 2016/02/13 15:01:29 by pcrosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include <dirent.h>
# include <sys/xattr.h>
# include <sys/stat.h>
# include <time.h>
# define DARWIN_FEATURE_64_BIT_INODE = 0

typedef struct s_file
{
	char *name;
	char *date;
	struct stat *info;
	struct s_file *next;
	struct s_file *prev;
}				t_file;

t_file *ft_retrieve(DIR *dir, t_file *begin);
t_file *ft_sort_lex(t_file *begin);
t_file *ft_l_display(t_file *begin);
t_file *ft_retrieves_date(t_file *begin);

#endif


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_options.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcrosnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/17 12:07:13 by pcrosnie          #+#    #+#             */
/*   Updated: 2016/02/17 15:49:23 by pcrosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/* Numeros des options -R = 1, -a = 2, -r = 3, -t = 4, -l = 5
*/
int		*ft_detect_option(char *path)
{
	int *options;
	int i;

	i = 0;
	options = (int *)malloc(sizeof(int) * 6);
	while (i < 6)
		options[i++] = 0;
	i = 0;
	if (path[0] != '-')
	{
		options[5] = 2;
		return (options);
	}
	(ft_strstr(path, "R") != NULL) ? options[i++] = 1 : i++;
	(ft_strstr(path, "a") != NULL) ? options[i++] = 1 : i++;
	(ft_strstr(path, "r") != NULL) ? options[i++] = 1 : i++;
	(ft_strstr(path, "t") != NULL) ? options[i++] = 1 : i++;
	(ft_strstr(path, "l") != NULL) ? options[i++] = 1 : i++;
	return (options);
}

void	ft_set_options(DIR *dir, t_file *begin, char **path, int path_size)
{
	int i;
	int *options;

	i = 1;
	options = ft_detect_option(path[i]);
	if (options[5] != 2)
		i++;
//	if (option[0] == 1)
//		ft_R_option()
	if (i == path_size)
	{
		path_size++;
		path[i] = ".";
	}
	while (i < path_size)
	{
		dir = opendir(path[i]);
		if (!dir)
			ft_error(path[i]);
		if (options && options[4] == 1)
			ft_l_option(path[i], begin, dir);
		else
		{
			begin = ft_retrieve(dir, begin, path[i]);
			begin = ft_sort_lex(begin);
			ft_print_list(begin, options[1], options[2]);
		}
		i++;
	}
}

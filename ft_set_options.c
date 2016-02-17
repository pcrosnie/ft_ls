/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_options.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcrosnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/17 12:07:13 by pcrosnie          #+#    #+#             */
/*   Updated: 2016/02/17 13:00:36 by pcrosnie         ###   ########.fr       */
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
	if (path[0] != '-')
		return (NULL);
	options = (int *)malloc(sizeof(int) * 6);
	options = ft_memset(options, 0, 6);
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
	if ((options = ft_detect_option(path[i])))
			i++;
//	if (option[0] == 1)
//		ft_R_option()
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
			ft_print_list(begin, 0, 0);
		}
		i++;
	}
}

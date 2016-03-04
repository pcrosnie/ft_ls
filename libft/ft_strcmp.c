/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcrosnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 17:39:48 by pcrosnie          #+#    #+#             */
/*   Updated: 2016/03/04 16:10:03 by pcrosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	int nb;

	nb = 0;
	if (ft_strlen(s1) > ft_strlen(s2))
		nb = ft_strlen(s2);
	else
		nb = ft_strlen(s1);
	return (ft_strncmp(s1, s2, nb + 1));
}

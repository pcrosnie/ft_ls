/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcrosnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 10:04:31 by pcrosnie          #+#    #+#             */
/*   Updated: 2016/02/13 11:51:22 by pcrosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_power(int n, int power)
{
	long		nb;

	nb = n;
	if (power == 0)
		return (1);
	while (power > 1)
	{
		nb *= n;
		power--;
	}
	return (nb);
}

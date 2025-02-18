/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mianni <mianni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:45:59 by jmenard           #+#    #+#             */
/*   Updated: 2024/11/14 17:34:14 by mianni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_white_space(const char *src)
{
	int	i;

	i = 0;
	while ((src[i] >= 9 && src[i] <= 13) || src[i] == 32)
		i++;
	return (i);
}

int	ft_atoi(const char *src)
{
	int	i;
	int	neg;
	int	n;

	i = ft_white_space(src);
	neg = 1;
	n = 0;
	if (!(src[i] >= 48 && src[i] <= 57))
	{
		if (src[i] == '-' || src[i] == '+')
		{
			if (src[i] == '-')
				neg = -1;
			i++;
		}
		if (!(src[i] >= 48 && src[i] <= 57))
			return (0);
	}
	while (src[i] && src[i] >= 48 && src[i] <= 57)
	{
		n *= 10;
		n += src[i] - 48;
		i++;
	}
	return (n *= neg);
}

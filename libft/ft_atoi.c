/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:18:54 by mleitner          #+#    #+#             */
/*   Updated: 2022/10/06 15:19:07 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int		i;
	int		pre;
	long	value;

	i = 0;
	pre = 1;
	value = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-')
		pre = -pre;
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	while (ft_isdigit(nptr[i]) && nptr[i] != '\0')
	{
		value = value * 10;
		value = value + (nptr[i] - 48);
		i++;
		if (value * pre > 2147483648)
			return (-1);
		else if (value * pre < -2147483648)
			return (0);
	}
	return ((int)value * pre);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:55:12 by mleitner          #+#    #+#             */
/*   Updated: 2022/10/06 17:28:06 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_checklen(int n)
{
	int		len;

	len = 0;
	if (n < 0)
	{
		len++;
		n = -n;
	}
	else if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static char	*ft_except(char *s, int n)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc((sizeof(char) * (n + 1)));
	while (s[i] != '\0')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static int	ft_sign(int n, char *str)
{
	if (n < 0)
	{
		*str = '-';
		return (-n);
	}
	return (n);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		div;

	if (n == -2147483648)
		return (ft_except("-2147483648", 11));
	else if (n == 0)
		return (ft_except("0", 1));
	div = n;
	len = ft_checklen(n);
	str = malloc((sizeof(char) * (len + 1)));
	if (!str)
		return (0);
	n = ft_sign(n, str);
	str[len] = '\0';
	while (n > 0)
	{
		div = n % 10;
		n = n / 10;
		str[--len] = div + 48;
	}
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 12:47:02 by mleitner          #+#    #+#             */
/*   Updated: 2022/10/06 14:21:56 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*src2;
	char	*dest2;

	if (dest == src || n == 0)
		return (dest);
	dest2 = (char *)dest;
	if (src < dest)
	{
		src2 = (char *)src + (n - 1);
		dest2 = (char *)dest + (n - 1);
		while (n--)
			*dest2-- = *src2--;
	}
	else
	{
		src2 = (char *)src;
		dest2 = (char *)dest;
		while (n--)
			*dest2++ = *src2++;
	}
	return (dest);
}

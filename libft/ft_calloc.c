/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:54:44 by mleitner          #+#    #+#             */
/*   Updated: 2022/10/13 14:50:25 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;
	size_t	val;

	val = nmemb * size;
	if (nmemb != 0 && val / nmemb != size)
		return (NULL);
	ptr = malloc(val);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, val);
	return ((void *)ptr);
}

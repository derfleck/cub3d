/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:42:33 by mleitner          #+#    #+#             */
/*   Updated: 2022/10/06 17:26:26 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_toolarge(void)
{
	char	*sub;

	sub = malloc(sizeof(char) * 1);
	if (!sub)
		return (NULL);
	sub[0] = '\0';
	return (sub);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*sub;
	size_t	l;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	l = ft_strlen(s);
	if (start >= l)
		return (ft_toolarge());
	while (s[start + i] != '\0' && i < (unsigned int) len)
		i++;
	sub = malloc((sizeof(char) * i) + 1);
	if (!sub)
		return (NULL);
	while (j < i)
	{
		sub[j] = s[start + j];
		j++;
	}
	sub[j] = '\0';
	return (sub);
}

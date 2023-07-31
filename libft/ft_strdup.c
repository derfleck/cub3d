/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:34:10 by mleitner          #+#    #+#             */
/*   Updated: 2022/10/05 16:30:55 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	int		j;
	char	*tab;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	tab = malloc((sizeof(char) * i) + 1);
	if (!tab)
		return (0);
	while (s[j] != '\0')
	{
		*(tab + j) = *(s + j);
		j++;
	}
	*(tab + j) = '\0';
	return (tab);
}

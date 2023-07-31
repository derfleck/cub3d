/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:10:39 by mleitner          #+#    #+#             */
/*   Updated: 2022/10/13 15:49:50 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_cntwrds(char const *s, char c)
{
	int	words;

	words = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			words++;
		while (*s != c && *s)
			s++;
	}
	return (words);
}

static char	*ft_strcpy(const char *s, char c)
{
	int		i;
	int		j;
	char	*tab;

	i = 0;
	j = 0;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
	}
	tab = malloc((sizeof(char) * (i + 1)));
	if (!tab)
		return (0);
	while (s[j] != c && s[j] != '\0')
	{
		*(tab + j) = *(s + j);
		j++;
	}
	*(tab + j) = '\0';
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char			**split;
	unsigned int	j;

	j = 0;
	if (!s)
		return (NULL);
	split = malloc(sizeof(char *) * (ft_cntwrds(s, c) + 1));
	if (!split)
		return (NULL);
	while (*s != '\0')
	{
		while (*s == c)
			s++;
		if (*s != c && *s != '\0')
		{
			split[j] = ft_strcpy(s, c);
			j++;
		}
		while (*s != c && *s != '\0')
			s++;
	}
	split[j] = 0;
	return (split);
}

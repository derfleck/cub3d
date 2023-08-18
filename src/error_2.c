/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 12:12:52 by mleitner          #+#    #+#             */
/*   Updated: 2023/08/18 12:12:52 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	safe_free_cmap(t_map *map)
{
	int	i;

	i = -1;
	while (map->cmap[++i])
		safe_free(map->cmap[i]);
	safe_free(map->cmap);
}

void	safe_free_fd_params_cmap(t_map *map, int fd)
{
	char	*str;

	str = NULL;
	buffer_cleaner(fd, str);
	safe_free_params(map);
	safe_free_cmap(map);
	exit (1);
}

/* Special case - frees params, cmap and imap till i */
void	free_all_previous(t_map *map, int i)
{
	int	j;

	safe_free_params(map);
	safe_free_cmap(map);
	j = -1;
	while (++j < i)
		safe_free(map->map[j]);
	safe_free(map->map);
	exit (1);
}

//frees int array up to a certain specified size
void	free_int_arr(int **arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
		free(arr[i++]);
	if (arr)
		free(arr);
}

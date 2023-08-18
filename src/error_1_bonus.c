/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_1_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 12:12:30 by mleitner          #+#    #+#             */
/*   Updated: 2023/08/18 12:12:34 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

void	safe_free(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
}

void	err_before_mall(char *str)
{
	ft_putstr_fd("Error\n", 2);
	ft_putendl_fd(str, 2);
	exit (1);
}

void	buffer_cleaner(int fd, char *str)
{
	if (fd > 2)
	{
		while (1)
		{
			str = get_next_line(fd);
			if (!str)
				break ;
			safe_free(str);
		}
		if (close(fd) == -1)
			ft_putendl_fd("Closing a file descriptor has failed!", 2);
	}
}

void	systemfail(t_map *map, int fd, char *str, char *message)
{
	if (message)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putendl_fd(message, 2);
	}
	safe_free(str);
	buffer_cleaner(fd, str);
	safe_free_params(map);
	exit (1);
}

void	safe_free_params(t_map *map)
{
	int	i;

	i = -1;
	while (++i < 4)
		safe_free(map->path[i]);
	safe_free(map->path);
}

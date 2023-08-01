/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmocsai <rmocsai@student.42.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:46:36 by mleitner          #+#    #+#             */
/*   Updated: 2023/07/31 14:36:05 by rmocsai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*
//combines string with new lines read of file
char	*line_unite(char *str1, char *str2)
{
	char	*tmp;

	if (!str1 || !str2)
		return (NULL);
	tmp = ft_strjoin(str1, str2);
	free(str1);
	free(str2);
	return (tmp);
}

static t_map	*parse_map(int fd)
{
	t_map	*map;
	char	*tmp;
	int		x;

	map = malloc(sizeof(t_map));
	if (!map)
		err_before_mall("Malloc for map failed");
	map->x_max = 0;
	map->y_max = 0;
	tmp = get_next_line(fd);
	if (tmp)
		map->str = ft_strdup("");
	while (tmp)
	{
		x = ft_strlen(tmp);
		if (x > map->x_max && tmp[x - 1] == "1")
			map->x_max = x;
		map->str = line_unite(map->str, tmp);
		map->y_max++;
		tmp = get_next_line(fd);
	}
	if (tmp)
		free(tmp);
	return (map);
}
*/

int	main(int argc, char **argv)
{
	t_map	*map;

	map = check_input(argc, argv);
	if (!map)
		return (1);
	return (0);
}

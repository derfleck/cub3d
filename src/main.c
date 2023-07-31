/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:46:36 by mleitner          #+#    #+#             */
/*   Updated: 2023/07/31 13:13:15 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*
static void	err_before_mall(char *str)
{
	printf("%s\n", str);
	exit (1);
}

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

int	main(int argc, char **argv)
{
	int		fd;
	t_map	*map;

	if (argc <= 1 || argc > 2 || (argc == 2 && !ends_with(argv[1], ".cub")))
		err_before_mall("Only .cub file required as parameter");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		err_before_mall("Couldn't open provided file");
	map = parse_map(fd);
}
*/

int main(int argc, char **argv)
{
	
}

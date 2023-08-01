#include "../inc/cub3d.h"

void	print_map(char **map)
{
	unsigned int	x;
	unsigned int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			ft_printf("%c", map[y][x]);
			x++;
		}
		y++;
		ft_printf("\n");
	}
}

int	check_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd <= 0)
		return (0);
	if (close(fd) == -1)
		return (0);
	return (1);
}

static int	ends_with(char *str, char *key)
{
	int	start;
	int	i;

	start = ft_strlen(str) - ft_strlen(key);
	i = 0;
	while (start && str[start] && key[i] && (str[start] == key[i]))
		i++;
	if (i == ft_strlen(key))
		return (1);
	return (0);
}

int	check_before_start(argc, argv)
{
	if (!check_file(map->so) || !check_file(map->no) || \
	!check_file(map->ea) || !check_file(map->we))
		return (1);
	return (0);
}

t_map	*check_input(int argc, char **argv)
{
	if (argc <= 1 || argc > 2 || (argc == 2 && !ends_with(argv[1], ".cub")) \
	|| (argc == 2 && !check_file(argv[1])))
		err_before_mall("Only .cub file required as parameter");



}

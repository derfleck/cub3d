#include "../inc/cub3d.h"

static int	is_num(char val)
{
	if (val >= '0' && val <= '9')
		return (1);
	return (0);
}

static void	init_arr(int *rgb, int size)
{
	int	i;

	i = 0;
	while (i < size)
		rgb[i++] = 0;
}

static int	check_colorcode(char **line, t_map *map, int fd)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	if (*line)
	{
		tmp = ft_strtrim(*line, "FC \n");
		if (tmp == NULL)
			systemfail(map, fd, *line, "Malloc failed!");
		safe_free(*line);
		*line = tmp;
	}
	else
		return (0);
	i = -1;
	while (tmp[++i])
	{
		if (!ft_strchr("0123456789 ,", tmp[i]))
			systemfail(map, fd, *line, "Color codes are invalid!");
	}
	return (1);
}

//converts a single line in the format 0,0,0 to color code
//IMPORTANT: check if format is correct before
//free line in all cases!!!
int	rgb_to_hex(char *line, t_map *map, int fd)
{
	int	i;
	int	j;
	int	rgb[3];

	if (!check_colorcode(&line, map, fd))
		systemfail(map, fd, line, "Color codes are invalid!");
	i = 0;
	j = 0;
	init_arr(rgb, 3);
	while (line[i] && j < 3)
	{
		while (line[i] && !is_num(line[i]))
			i++;
		while (is_num(line[i]))
		{
			rgb[j] = rgb[j] * 10;
			rgb[j] = rgb[j] + (line[i] - '0');
			i++;
		}
		if (rgb[j] > 255 || rgb[j] < 0)
			systemfail(map, fd, line, "Color codes are invalid!");
		j++;
	}
	safe_free(line);
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

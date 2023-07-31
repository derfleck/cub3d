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

//converts a single line in the format 0,0,0 to color code
//IMPORTANT: check if format is correct before
int	rgb_to_hex(char *line)
{
	int	i;
	int	j;
	int	rgb[3];

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
		j++;
	}
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:38:57 by mleitner          #+#    #+#             */
/*   Updated: 2023/08/07 17:00:52 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../mlx_linux/mlx.h"
# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include <X11/keysym.h>
# include <errno.h>
# define WIDTH 800
# define HEIGHT 600
# define GRID 10
# define BLACK 0x00000000
# define BLUE  0x000000FF
# define GREEN 0x0000FF00
# define RED 0x00FF0000
# define YELLOW 0x00FFFF00
# define WHITE 0x00FFFFFF
# define BUFFER_SIZE 1000
# define X 0
# define Y 1

//structure for coordinates, using 2D single linked list
typedef struct s_pt {
	float_t		x;
	float_t		y;
	struct s_pt	*right;
	struct s_pt	*up;
}	t_pt;

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_mlx {
	void	*mlx;
	void	*win;
	t_img	*img;
}	t_mlx;

typedef enum e_dir {
	NORTH = 0,
	EAST,
	SOUTH,
	WEST
}	t_dir;

typedef struct s_map {
	int		**map;
	int		look_dir[2];
	int		player[2];
	int		mini_max[2];
	int		max[2];
	char	**tex;
	int		ceiling;
	int		floor;
	t_mlx	*mlx;
}	t_map;

typedef struct s_player {
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	time;
	double	prev_time;
}	t_player;

//struct for line points
typedef struct s_line {
	int	x0;
	int	x1;
	int	y0;
	int	y1;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
}	t_line;

//draw functions
void	ft_mlx_pixel_put(t_img *img, int x, int y, int color);

//minimap functions
void	draw_cube(t_img *img, int *pos, int len, int col);
void	free_int_arr(int **arr, int size);
int		**get_int_array(int x, int y);
int		**get_minimap(t_map *map);
void	set_dimensions(t_map *map);
void	draw_minimap(t_map *map);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:38:57 by mleitner          #+#    #+#             */
/*   Updated: 2023/08/08 14:56:26 by mleitner         ###   ########.fr       */
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
# include <float.h>
# define WIDTH 800
# define HEIGHT 600
# define GRID 8
# define TEX 64
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

typedef struct s_player	t_player;

typedef struct s_map {
	int			**map;
	int			max[2];
	int			mini_max[2];
	char		**tex;
	int			ceiling;
	int			floor;
	char		dir;
	t_player	*play;
	t_mlx		*mlx;
}	t_map;

typedef struct s_player {
	double	player[2];
	double	plane[2];
	double	look_dir[2];
	t_map	*map;

	double	camera_x;
	double	raydir[2];
	double	sidedist[2];
	double	deltadist[2];
	int		step[2];
	double	perpwalldist;

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
void	draw_cube(t_img *img, int *pos, int len);
void	free_int_arr(int **arr, int size);
int		**get_int_array(int x, int y);
void	draw_minimap(t_map *map);

//raycasting
void	raycast(t_map *map);
void	set_direction(t_map *map);
void	draw_wall(t_map *map, int x);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmocsai <rmocsai@student.42.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:38:57 by mleitner          #+#    #+#             */
/*   Updated: 2023/08/14 13:26:10 by rmocsai          ###   ########.fr       */
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
# define TARGET_FPS 500
# define PRINT_FPS 1
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

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
	SOUTH,
	EAST,
	WEST
}	t_dir;

typedef struct s_map	t_map;

typedef struct s_player {
	double	player[2]; //starting position (x, y) set in the middle!! (x.5, y.5)
	double	plane[2];
	double	look_dir[2];
	t_map	*map;
	double	camera_x;
	double	raydir[2];
	double	sidedist[2];
	double	deltadist[2];
	int		step[2];
	double	perpwalldist;
	int		side;
	double	wall_x;
	double	tex_step;
	double	tex_pos;
	int		wall_height;
	int		tex_i[2];
	int		screen_pos[2];
	clock_t	prev_time;
}	t_player;

typedef struct s_map {
	int		**map; //has to be rectangular, no spaces, only 1s & 0s!!!
	int		max[2]; //map dimensions (max x, max y)
	char	**paths;
	int		ceiling;
	int		floor;
	char	**dir; //use enum (map.dir[NORTH] = ft_strdup"./maps/map1.cub")

	t_img		tex[4];
	double		walk_speed;
	double		rot_speed;
	int			mini_max[2];
	int			mini_start[2];
	int			mini_end[2];
	t_player	play;
	t_mlx		mlx;
}	t_map;

/* Check input */
t_map	*check_input(int argc, char **argv, t_map *map);
int		check_file(char *file);
int		ends_with(char *str, char *key);

/* Error handling */
void	safe_free_params(t_map *map);
void	safe_free(void *ptr);
void	err_before_mall(char *str);
void	systemfail(t_map *map, int fd, char *str, char *message);

/* Parsing */
int		get_lines(t_map *map, char *file);
int		rgb_to_hex(char *line, t_map *map, int fd);

/*  */
void	ft_mlx_pixel_put(t_img *img, int x, int y, int color);

#endif
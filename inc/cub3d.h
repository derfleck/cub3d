/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:38:57 by mleitner          #+#    #+#             */
/*   Updated: 2023/08/14 16:26:11 by mleitner         ###   ########.fr       */
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
# include <time.h>
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
# define TARGET_FPS 0
# define PRINT_FPS 0
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

//content of path also need to follow this order, as
//they're loaded into the tex array in the same
typedef enum e_dir {
	NORTH = 0,
	EAST,
	SOUTH,
	WEST
}	t_dir;

typedef struct s_map	t_map;

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
	int		side;
	
	double	wall_x;
	double	tex_step;
	double	tex_pos;
	int		wall_height;
	int		tex_i[2];
	int		screen_pos[2];

	clock_t	prev_time;
	int		walk;
	int		strafe;
	int		rotate;
}	t_player;

typedef struct s_map {
	int			**map;
	int			max[2];
	char		**path;
	int			ceiling;
	int			floor;
	char		dir;
	
	t_img		tex[4];
	double		walk_speed;
	double		rot_speed;
	int			mini_max[2];
	int			mini_start[2];
	int			mini_end[2];
	t_player	play;
	t_mlx		mlx;
}	t_map;


//struct for line points
typedef struct s_line {
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
}	t_line;

//helper struct for matrix multiplication
typedef struct s_mat {
	double	c1r1;
	double	c1r2;
	double	c2r1;
	double	c2r2;
}	t_mat;

//draw and math utils
void	ft_mlx_pixel_put(t_img *img, int x, int y, int color);
int		get_color_value(t_map *map, int x, int y, int i);
double	deg_to_rad(double deg);
void	mat_mul(double *val, t_mat mat);

//line drawing
void	ft_mlx_line(t_img *img, int *start, int *end, int color);

//minimap functions
void	draw_minimap(t_map *map);

//raycasting and drawing
void	raycast(t_map *map);
void	set_direction(t_map *map);
void	draw_wall(t_map *map, int x);
void	draw_background(t_map *map);

//textures
void	load_textures(t_map *map);
void	draw_wall_textured(t_map *map, int x);

//hooks
void	set_hooks(t_map *map);

//move
void	calc_speed(t_player *play);
void	walk(t_map *map, int dir);
void	strafe(t_map *map, int dir);
void	rotate(t_map *map, double ang);

#endif
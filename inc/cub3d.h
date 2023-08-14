/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmocsai <rmocsai@student.42.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:38:57 by mleitner          #+#    #+#             */
/*   Updated: 2023/08/02 16:37:25 by rmocsai          ###   ########.fr       */
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

//structure for coordinates, using 2D single linked list
typedef enum e_dir {
	NORTH = 1,
	SOUTH,
	EAST,
	WEST
}	t_dir;

typedef struct s_pt {
	float_t		x;
	float_t		y;
	float_t		z;
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

typedef struct s_map {
	int		**map; //has to be rectangular, no spaces, only 1s & 0s!!!
	int		start_orientation; //use enum!!!
	int		start_position_x; // save posi here then change it in arr to 0
	int		start_position_y; //as above
	int		y_max; //map dimensions
	int		x_max; //map dimensions
	char	*so;
	char	*we;
	char	*ea;
	char	*no;
	int		ceiling;
	int		floor;
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
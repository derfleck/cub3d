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
	double		player[2];
	double		plane[2];
	double		look_dir[2];
	t_map		*map;
	double		camera_x;
	double		raydir[2];
	double		sidedist[2];
	double		deltadist[2];
	int			step[2];
	double		perpwalldist;
	int			side;
	double		wall_x;
	double		tex_step;
	double		tex_pos;
	int			wall_height;
	int			tex_i[2];
	int			screen_pos[2];
	clock_t		prev_time;
}	t_player;

typedef struct s_map {
	int			index;
	char		**cmap;
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

/* Check input */
t_map	*check_input(int argc, char **argv, t_map *map);
int		check_file(char *file);
int		ends_with(char *str, char *key);
int		check_map_validity(t_map *map);
int		check_walls(t_map *map);
int		check_neighbors(t_map *map, int x, int y);

/* Error handling */
void	safe_free(void *ptr);
void	safe_free_params(t_map *map);
void	safe_free_cmap(t_map *map);
void	err_before_mall(char *str);
void	systemfail(t_map *map, int fd, char *str, char *message);
void	safe_free_fd_params_cmap(t_map *map, int fd);
void	free_all_previous(t_map *map, int i);
void	safe_free_map(t_map *map);
void	free_all_no_exit(t_map *map);
void	free_all_with_exit(t_map *map);
void	buffer_cleaner(int fd, char *str);

/* Parsing */
int		get_lines(t_map *map, char *file);
int		rgb_to_hex(char *line, t_map *map, int fd);
int		get_map(t_map *map, int fd, char *line, char *file);
char	*trim_spaces(char *line, t_map *map, int fd);
char	*fill_params(char *line, t_map *map, int fd);
int		count_rows(t_map *map);
int		count_columns(t_map *map);
int		trim_newlines(t_map *map);
void	cmap_to_imap(t_map *map);

/* Utils */
void	close_fd(int fd, t_map *map);
void	ft_mlx_pixel_put(t_img *img, int x, int y, int color);
void	linecheck_helper1(t_map *map, char *line, int fd, int dir);
void	linecheck_helper2(t_map *map, char *line, int fd, char c);

/* To remove - ONLY FOR DEBUG */
void	print_map(char **map);

#endif
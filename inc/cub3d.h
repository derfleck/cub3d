#ifndef CUB3D_H
# define CUB3D_H
# include "../mlx_linux/mlx.h"
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
	int		x_max;
	int		y_max;
	char	*str;
}	t_map;

typedef enum e_dir {
	FLOOR,
	NORTH,
	SOUTH,
	EAST,
	WEST
}	t_dir;

char	*get_next_line(int fd);

void	ft_mlx_pixel_put(t_img *img, int x, int y, int color);
int		ends_with(char *str, char *key);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);

#endif
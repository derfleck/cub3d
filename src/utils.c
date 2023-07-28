#include "../inc/cub3d.h"

//writes pixel on image
void	ft_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	i;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = malloc((sizeof(char) * (len1 + len2 + 1)));
	if (!str)
		return (0);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[i - len1] != '\0')
	{
		str[i] = s2[i - len1];
		i++;
	}
	str[i] = '\0';
	return (str);
}

//checks if str ends with key
//key needs to be larger than 0 characters
int	ends_with(char *str, char *key)
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

static void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(unsigned char *)(s + i) = '\0';
		i++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;
	size_t	val;

	val = nmemb * size;
	if (nmemb != 0 && val / nmemb != size)
		return (NULL);
	ptr = malloc(val);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, val);
	return ((void *)ptr);
}

char	*ft_strdup(const char *s)
{
	int		i;
	int		j;
	char	*tab;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	tab = malloc((sizeof(char) * i) + 1);
	if (!tab)
		return (NULL);
	while (s[j] != '\0')
	{
		*(tab + j) = *(s + j);
		j++;
	}
	*(tab + j) = '\0';
	return (tab);
}

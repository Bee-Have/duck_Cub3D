#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "libft.h"
#include "mlx.h"

#ifndef CUB3D_H
#define CUB3D_H

typedef struct s_color
{
	unsigned char	a;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned int	code;
}			t_color;

typedef struct s_vec2
{
	int	x;
	int	y;
}			t_vec2;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_pxl;
	int		line_len;
	int		endian;
	int		pxl_unit;
}			t_img;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	img;

	char	**map;
}			t_mlx;

#endif
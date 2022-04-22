#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "libft.h"
#include "ft_get_file.h"
#include "mlx.h"

#ifndef CUB3D_H
#define CUB3D_H

typedef struct s_pos
{
	float	x;
	float	y;
}			t_pos;

typedef struct s_vec2
{
	int	x;
	int	y;
}			t_vec2;

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		bits_per_pxl;
	int		line_length;
	int		endian;
}			t_img;

typedef struct s_mlx
{
	void	*mlx;
	void	*mlx_win;
	t_img	img;

	char	**map;
}			t_mlx;

#endif
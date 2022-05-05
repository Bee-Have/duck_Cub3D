#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "libft.h"
#include "mlx.h"

#ifndef CUB3D_H
#define CUB3D_H

typedef struct s_vec2
{
	int	x;
	int	y;
}			t_vec2;

typedef struct s_pos
{
	float	x;
	float	y;
}			t_pos;

typedef struct s_pj
{
	t_pos	pos;
	int		rot;
}			t_pj;

typedef struct s_color
{
	unsigned char	a;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned int	code;
}			t_color;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_pxl;
	int		line_len;
	int		endian;
}			t_img;

typedef struct s_event
{
	char	is_w_pressed;
	char	is_a_pressed;
	char	is_s_pressed;
	char	is_d_pressed;
	char	is_left_pressed;
	char	is_right_pressed;
}			t_event;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	img;

	t_event	event;

	t_vec2	screen;
	char	**map;
	t_pj	pj;
}			t_mlx;

#endif
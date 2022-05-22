#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "libft.h"
#include "mlx.h"

#ifndef CUB3D_H
#define CUB3D_H

// minimap general position
#define T_LEFT 0
#define T_RIGHT 1
#define B_LEFT 2
#define B_RIGHT 3
#define CENTER 4

// keycodes :
#define ESC 65307
#define UP 119
#define DOWN 115
#define RIGHT 100
#define LEFT 97
#define R_RIGHT 65363
#define R_LEFT 65361

// gameplay pj
#define SPEED 0.1
#define R_SPEED 5

// structs
typedef struct s_vec2
{
	int	x;
	int	y;
}			t_vec2;

typedef struct s_pos
{
	double	x;
	double	y;
}			t_pos;

typedef struct s_pj
{
	t_pos	pos;
	t_pos	dir;
	t_pos	plane;
	int		rot;
}			t_pj;

typedef struct s_map_info
{
	char	**map;
	int		pxl_unit;
	t_vec2	screen;
}			t_map_info;

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

	t_map_info	map_info;
	t_pj	pj;
}			t_mlx;

//? INIT
// structs
t_map_info	init_map_info(char **map, int width, int height);
// mlx
t_img	init_img(void);
t_mlx	*init_mlx(int width, int height);
// gameplay
t_pj	init_pj(char **map);

//? ROUTINE
// mlx
void	mlx_routine(t_mlx *mlx);
// update
int		update_all(t_mlx *mlx);
// keys events
int		key_press(int keycode, t_mlx *mlx);
int		key_release(int keycode, t_mlx *mlx);
int		update_keys_events(t_mlx *mlx);
// raycasting
void	raycasting_routine(t_mlx *mlx);

#endif
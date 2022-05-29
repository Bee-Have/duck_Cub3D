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
typedef struct s_int2
{
	int	x;
	int	y;
}			t_int2;

typedef struct s_vec2
{
	double	x;
	double	y;
}			t_vec2;

typedef struct s_pj
{
	t_vec2	pos;
	int		rot;
	t_vec2	dir;
	t_vec2	plane;
}			t_pj;

typedef struct s_color
{
	unsigned char	a;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned int	code;
}					t_color;

typedef struct s_raycasting
{
	int		x;
	t_vec2	side_dist;
	t_vec2	delta_dist;
	t_int2	step;
	int		side;
}				t_raycast;

typedef struct s_screen_info
{
	t_int2	screen;
	char	**map;
	int		pxl_unit;

	t_color	floor;
	t_color	ceiling;
	t_color	wall_north;//tmp
	t_color	wall_south;//tmp
	t_color	wall_east;//tmp
	t_color	wall_west;//tmp
}			t_screen_info;

typedef struct s_event
{
	char	is_w_pressed;
	char	is_a_pressed;
	char	is_s_pressed;
	char	is_d_pressed;
	char	is_left_pressed;
	char	is_right_pressed;
}			t_event;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_pxl;
	int		line_len;
	int		endian;
}			t_img;

typedef struct s_textures
{
	t_img	north_texture;
	t_img	south_texture;
	t_img	west_texture;
	t_img	east_texture;
}			t_textures;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	img;
}			t_mlx;

typedef struct s_system
{
	t_mlx			mlx;
	t_textures		textures;

	t_screen_info	s_i;
	t_event			events;
	t_pj			pj;
}			t_system;

//? INIT
// structs
t_int2			make_int2(int y, int x);
t_vec2			make_vec2(double y, double x);
t_color			make_color(unsigned char a, unsigned char r, unsigned char g, unsigned char b);
t_screen_info	init_screen_info(char **map, int width, int height);
// mlx
t_img	init_img(void);
t_event	init_events(void);
t_mlx	init_mlx(int width, int height);
// gameplay
t_pj	init_pj(char **map);

//? ROUTINE
// mlx
void	mlx_routine(t_system *sys);
// update
int		update_all(t_system *sys);
// keys events
int		key_press(int keycode, t_system *sys);
int		key_release(int keycode, t_system *sys);
int		update_keys_events(t_system *sys);
// raycasting
void	raycasting_routine(t_system *sys);
// drawing tools
void	draw_pxl(t_system *sys, t_int2 pos, t_color color);
void	draw_square(t_system *sys, t_color color, t_int2 pos, int size);
void	draw_line(t_system *sys, t_int2 start, t_int2 end, t_color color);
void	draw_circle(t_system *sys, t_color color, t_int2 pos, int size);

//? PARSING

# define ERROR_LIMIT 20

# define P_ERR_NO "Error\nMultiple definition of North texture at line "
# define P_ERR_SO "Error\nMultiple definition of South texture at line "
# define P_ERR_WE "Error\nMultiple definition of West texture at line "
# define P_ERR_EA "Error\nMultiple definition of East texture at line "
# define P_ERR_F "Error\nMultiple definition of Floor color at line "
# define P_ERR_C "Error\nMultiple definition of Ceiling color at line "
# define P_ERR_UNKNOWN_PARAM "Error\nUnrecognized parameter at line "
# define P_ERR_MISSING_PARAM "Error\nMissing parameter at line "
# define P_ERR_MISSING_MAP "Error\nMissing map at line "
# define P_ERR_UNVALID_CHAR "Error\nUnvalid character at line "
# define P_ERR_START_POS "Error\nMultiple definition of start position at line "
# define P_ERR_UNCLOSED_MAP "Error\nMap is not closed at line "

/*
* This struct is used for the parsing of the map file.
* It will keep track of what elements has been found in the map file.
* It will also store a list of errors that occured during the parsing.
*/
typedef struct s_parser
{
	unsigned char	north_texture_count;
	unsigned char	south_texture_count;
	unsigned char	west_texture_count;
	unsigned char	east_texture_count;
	unsigned char	floor_color_count;
	unsigned char	ceil_color_count;
	unsigned char	start_pos_count;
	char			errors[ERROR_LIMIT][100];
	int				error_count;
}	t_parser;

/*
*	Print an error if one of the parameters is missing.
*	Print every encountered error.
*	Return 0 if no errors, the number of errors otherwise.
*/
int	end_parser(const t_parser *parser);

/*
*	Will format an error message if the error count is less than 20.
*	This function still use dynamic allocation for atoi.
*/
void	add_error(t_parser *parser, const char *description
	, int line, int column);

/*
*	Will recognize the token and increment the corresponding counter.
*/
void	add_to_args_count(t_parser *parser, char token, char next_token);

/*
*	Parse the map content.
*	Return the line position of the map.
*/
int	parse_map_content(t_d_list *lines, t_parser *parser);

/*
*	This function will run tests on the path and then on the file.
* If everything is correct the map data will be saved in the mlx struct.
* Return 0 on success, 1 on error.
*/
int	parse_map(t_system *sys, char *file);

#endif
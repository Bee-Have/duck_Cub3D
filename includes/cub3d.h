/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:56:34 by user42            #+#    #+#             */
/*   Updated: 2022/06/28 02:58:04 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <limits.h>
# include "libft.h"
# include "mlx.h"

// window/screen size
# define W_HEIGHT 1080
# define W_WIDTH 1920

// keycodes :
# define ESC 65307
# define UP 119
# define DOWN 115
# define RIGHT 100
# define LEFT 97
# define R_RIGHT 65363
# define R_LEFT 65361

// gameplay pj
# define DIR 0.7
# define PLANE 0.7
# define SPEED 0.2
# define R_SPEED 0.1

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

//m = slope of line
typedef struct s_line_info
{
	t_int2	start;
	t_int2	end;
	t_int2	m;
	int		decide;
	int		err;
}			t_line_info;

typedef struct s_raycasting
{
	int		x;
	int		wall_height;
	t_int2	hit;
	t_vec2	ray_dir;
	t_vec2	side_dist;
	t_vec2	delta_dist;
	t_int2	wall_limits;
	t_int2	step;
	int		side;
}				t_raycast;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_pxl;
	int		line_len;
	int		endian;
	t_int2	size;
}			t_img;

typedef struct s_screen_info
{
	char	**map;
	int		map_height;
	int		map_width;
	int		pxl_unit;

	t_color	floor;
	t_color	ceiling;
	t_img	north_texture;
	t_img	south_texture;
	t_img	west_texture;
	t_img	east_texture;
	t_img	error_texture;
}			t_screen_info;

typedef struct s_event
{
	char	is_w_pressed;
	char	is_a_pressed;
	char	is_s_pressed;
	char	is_d_pressed;
	char	is_left_pressed;
	char	is_right_pressed;
	char	is_m_pressed;
	char	is_v_pressed;
}			t_event;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	img;
}			t_mlx;

typedef struct s_system
{
	t_mlx			mlx;

	t_screen_info	s_i;
	t_event			events;
	t_pj			pj;
}			t_system;

//? INIT
// structs
t_int2	make_int2(int y, int x);
t_vec2	make_vec2(double y, double x);
t_color	make_color(unsigned char a, unsigned char r, unsigned char g,
			unsigned char b);
// mlx
t_img	init_img(void);
t_event	init_events(void);
t_mlx	init_mlx(char window_name[10]);
// gameplay
t_pj	init_pj(char **map);

//? ROUTINE
// mlx
void	mlx_routine(t_system sys);
// update
int		update_all(t_system *sys);
// keys events
int		key_press(int keycode, t_system *sys);
int		key_release(int keycode, t_system *sys);
void	rotate_player(t_system *sys, char dir, double speed);
int		update_keys_events(t_system *sys);
// raycasting
void	raycasting_routine(t_system *sys);
void	texture_calculations(t_system *sys, t_raycast cast_info,
			double wall_dist);
// drawing tools
void	draw_pxl(t_system *sys, t_int2 pos, t_color color);
void	draw_square(t_system *sys, t_color color, t_int2 pos, int size);
void	draw_rect(t_system *sys, t_color color, t_int2 pos, t_int2 size);
void	draw_line(t_system *sys, t_int2 start, t_int2 end, t_color color);
void	draw_circle(t_system *sys, t_color color, t_int2 pos, int size);

//? END SIMULATION
int		end_simulation(t_system *sys, int exit_code);
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
# define P_ERR_COLOR "Error\nInvalid color formatting at line "
# define P_ERR_TEXTURE "Error\nInvalid texture at line "

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
	size_t			line_max_size;
}	t_parser;

/*
*	Print an error if one of the parameters is missing.
*	Print every encountered error.
*	Return 0 if no errors, the number of errors otherwise.
*/
int		end_parser(const t_parser *parser);

/*
*	Will format an error message if the error count is less than 20.
*	This function still use dynamic allocation for atoi.
*/
void	add_error(t_parser *parser, const char *description,
			int line, int column);

/*
*	Will recognize the token and increment the corresponding counter.
*/
void	add_to_args_count(t_parser *parser, char token, char next_token);

/*
*	Parse the map content.
*	Return the line position of the map.
*/
int		parse_map_content(t_d_list *lines, t_parser *parser);

/*
*	This function will run tests on the path and then on the file.
*	If everything is correct the config data will be saved in the system struct.
*	Return 0 on success, 1 on error.
*/
int		parse_map(t_system *sys, char *file);

/*
*	Fill the correct system struct with the data of the line.
*	If not valid, add an error to the parser.
*/
void	init_config(t_system *sys, char *line, t_int2 pos, t_parser *parser);

/*
*	Take what have been parsed and fill the system struct.
*	If an error occured, the map is not allocated.
*/
void	init_map(t_system *sys, t_d_list lines, t_int2 pos, t_parser *parser);

/*
*	Check either if the value is a power of two or zero.
*/
char	is_power_of_two(int x);

#endif
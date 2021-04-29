/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 12:31:36 by user42            #+#    #+#             */
/*   Updated: 2021/04/29 17:18:16 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
#include "../libraries/libft/libft.h"
#include "../libraries/ft_get_file/ft_get_file.h"
#include "../libraries/minilibx-linux/mlx.h"

typedef struct s_res
{
	int		width;
	int		height;
}				t_res;

typedef struct s_color
{
	int		R;
	int		G;
	int		B;
}				t_color;

typedef struct s_cub
{
	char	**file;
	t_res	*res;
	char	*no;
	char	*so;
	char	*ea;
	char	*we;
	char	*sprite;
	t_color	*floor;
	t_color	*ceiling;
	int		found_map;
	char	**map;
}				t_cub;

typedef struct s_vars
{
	void	*mlx;
	void	*mlx_win;
}				t_vars;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pix;
	int		line_length;
	int		endian;
	int		pxl_x;
	int		pxl_y;
}				t_data;

void	get_infos(char *path);
void	treat_infos(char *line, t_cub **list);

t_cub	*init_struct(void);
t_res	*init_resolution(void);
t_color	*init_colors(void);
t_vars	*init_mlx_vars(void);
t_data	*init_mlx_data(void);
void	free_list(t_cub **list);
void	free_2d_array(char ***array);

void	init_minilibx(t_cub **list);
void	my_mlx_pxl_put(t_data **data, int x, int y, int color);
int		key_hook(int keycode, t_vars **vars);
void	test_pxl_loop(t_data **data, t_vars **vars);;

void	res_RGB_register(t_cub **cub, char *str);
void	texture_register(t_cub **cub, char *str);

void	map_register(t_cub **cub, int *index);
void	map_open_check(t_cub **cub);
int		open_test(char **map, int i, int index);
void	map_pj_check(t_cub **cub);

void	simple_error(t_cub **cub, char *str);

//DEBUG (a enlever plus tard)
void	print_map(char **map);

#endif
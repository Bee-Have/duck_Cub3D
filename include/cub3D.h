/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 12:31:36 by user42            #+#    #+#             */
/*   Updated: 2021/04/28 15:27:01 by amarini-         ###   ########.fr       */
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

typedef struct s_list
{
	char	**file;
	char	**res;
	char	*no;
	char	*so;
	char	*ea;
	char	*we;
	char	*sprite;
	char	**floor;
	char	**ceiling;
	int		found_map;
	char	**map;
}				t_list;

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
void	treat_infos(char *line, t_list **list);

t_list	*init_struct(void);
t_vars	*init_mlx_vars(void);
t_data	*init_mlx_data(void);
void	free_list(t_list **list);
void	free_2d_array(char ***array);

void	init_minilibx(t_list **list);
void	my_mlx_pxl_put(t_data **data, int x, int y, int color);
int		key_hook(int keycode, t_vars **vars);
void	test_pxl_loop(t_data **data, t_vars **vars);;

char	**res_colors_register(char *str);
char	*texture_register(char *str);

char	**map_register(char **file, int *index);
void	map_open_check(char **map);
void	map_pj_check(char **map);

void	simple_error(char *str);

//DEBUG (a enlever plus tard)
void	print_map(char **map);

#endif
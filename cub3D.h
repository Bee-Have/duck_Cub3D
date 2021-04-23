/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 12:31:36 by user42            #+#    #+#             */
/*   Updated: 2021/04/23 13:42:26 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
#include <mlx.h>
#include "libft/libft.h"
#include "ft_get_file/ft_get_file.h"

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

void	get_infos(char *path);
void	treat_infos(char *line, t_list **list);

t_list	*init_struct(void);
void	free_list(t_list **list);
void	free_2d_array(char ***array);

char	**res_colors_register(char *str, int tab_size);
char	*texture_register(char *str);

char	**map_register(char **file, int *index);
void	map_open_check(char **map);
void	map_pj_check(char **map);

void	simple_error(char *str);

//DEBUG (a enlever plus tard)
void	print_map(char **map);

#endif
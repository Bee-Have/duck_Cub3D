/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 12:31:36 by user42            #+#    #+#             */
/*   Updated: 2021/04/20 16:11:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
#include "libft/libft.h"
#include "get_next_line/get_next_line.h"

typedef struct s_list
{
	int		*res;
	//texture NO
	//texture SO
	//texture WE
	//texture EA
	//texture SPRITE
	int		*floor;
	int		*ceiling;
	char	**map;
}				t_list;

void	get_infos(char *path);
void	treat_infos(char *line, t_list **list);

int		*calc_resolution(char *str, int tab_size);

t_list	*init_struct(void);

void	simple_error(void);

#endif
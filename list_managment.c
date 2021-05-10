/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_managment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 13:42:11 by user42            #+#    #+#             */
/*   Updated: 2021/05/10 16:29:27 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3D.h"

t_cub		*init_struct(void)
{
	t_cub	*cub;

	cub = NULL;
	cub = (t_cub *)malloc(sizeof(t_cub));
	if (!cub)
		return (NULL);
	cub->res = init_resolution();
	cub->ceiling = init_colors();
	cub->floor = init_colors();
	cub->found_map = 0;
	return (cub);
}

t_res		*init_resolution(void)
{
	t_res	*res;

	res = NULL;
	res = (t_res *)malloc(sizeof(t_res));
	if (!res)
		return (NULL);
	res->width = 0;
	res->height = 0;
	return (res);
}

t_color		*init_colors(void)
{
	t_color	*color;

	color = NULL;
	color = (t_color *)malloc(sizeof(t_color));
	if (!color)
		return (NULL);
	color->R = 0;
	color->G = 0;
	color->B = 0;
	return (color);
}

t_vars		*init_mlx_vars(void)
{
	t_vars	*mlx_vars;

	mlx_vars = NULL;
	mlx_vars = (t_vars *)malloc(sizeof(t_vars));
	if (!mlx_vars)
		return (NULL);
	mlx_vars->mlx = mlx_init();
	mlx_vars->mlx_win = NULL;
	return (mlx_vars);
}

t_data	*init_mlx_data(void)
{
	t_data	*mlx_lst;
	
	mlx_lst = NULL;
	mlx_lst = (t_data *)malloc(sizeof(t_data));
	if (!mlx_lst)
		return (NULL);
	mlx_lst->img = NULL;
	mlx_lst->bits_per_pix = 0;
	mlx_lst->line_length = 0;
	mlx_lst->endian = 0;
	mlx_lst->pxl_x = 5;
	mlx_lst->pxl_y = 5;
	return (mlx_lst);
}

t_all	*init_all(void)
{
	t_all	*all;

	all = NULL;
	all = (t_all *)malloc(sizeof(t_all));
	if (!all)
		return (NULL);
	return (all);
	all->cub = NULL;
	all->data = NULL;
	all->vars = NULL;
}

void		free_list(t_cub **list)
{
	free_2d_array(&(*list)->file);
	free((*list)->res);
	free((*list)->floor);
	free((*list)->ceiling);
	if ((*list)->map)
		free_2d_array(&(*list)->map);
	free((*list)->no);
	free((*list)->so);
	free((*list)->ea);
	free((*list)->we);
	free((*list)->sprite);
	free((*list));
}

void	free_2d_array(char ***array)
{
	int		index;

	index = 0;
	while ((*array)[index] != NULL)
	{
		free((*array)[index]);
		index++;
	}
	free((*array));
	return ;
}
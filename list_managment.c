/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_managment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 13:42:11 by user42            #+#    #+#             */
/*   Updated: 2021/04/28 18:12:48 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3D.h"

t_cub		*init_struct(void)
{
	t_cub	*list;
	
	list = NULL;
	list = (t_cub *)malloc(sizeof(t_cub));
	if (!list)
		return (NULL);
	list->found_map = 0;
	return (list);
}

t_vars	*init_mlx_vars(void)
{
	t_vars *mlx_vars;

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
	t_data *mlx_lst;
	
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

void		free_list(t_cub **list)
{
	free_2d_array(&(*list)->file);
	if ((*list)->res)
		free_2d_array(&(*list)->res);
	if ((*list)->floor)
		free_2d_array(&(*list)->floor);
	if ((*list)->ceiling)
		free_2d_array(&(*list)->ceiling);
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx_managment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 14:36:42 by amarini-          #+#    #+#             */
/*   Updated: 2021/04/27 16:27:55 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3D.h"

void	init_minilibx(t_list **list)
{
	void	*mlx;
	void	*mlx_win;
	void	*img;

	mlx_win = NULL;
	img = NULL;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, ft_atoi((*list)->res[0]), ft_atoi((*list)->res[1]), "cub3D");
	img = mlx_new_image(mlx, ft_atoi((*list)->res[0]), ft_atoi((*list)->res[0]));
	mlx_loop(mlx);
	return ;
}
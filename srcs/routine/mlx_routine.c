/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_routine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:35:55 by amarini-          #+#    #+#             */
/*   Updated: 2022/05/17 16:06:55 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	mlx_routine(t_mlx *mlx)
{
	// general routine for everything
	mlx_loop_hook(mlx->mlx, update_all, mlx);
	// key press
	mlx_hook(mlx->win, 2, 1L<<0, key_press, mlx);
	// key release
	mlx_hook(mlx->win, 3, 1L<<1, key_release, mlx);
	mlx_loop(mlx->mlx);
}

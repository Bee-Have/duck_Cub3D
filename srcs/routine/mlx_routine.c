/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_routine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:35:55 by amarini-          #+#    #+#             */
/*   Updated: 2022/05/30 16:51:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	mlx_routine(t_system sys)
{
	// general routine for everything
	mlx_loop_hook(sys.mlx.mlx, update_all, &sys);
	// key press
	mlx_hook(sys.mlx.win, 2, 1L<<0, key_press, &sys);
	// key release
	mlx_hook(sys.mlx.win, 3, 1L<<1, key_release, &sys);
	mlx_loop(sys.mlx.mlx);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_routine_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:35:55 by amarini-          #+#    #+#             */
/*   Updated: 2022/06/16 23:15:56 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duckling3d_bonus.h"

void	mlx_routine(t_system sys)
{
	// general routine for everything
	mlx_loop_hook(sys.mlx.mlx, update_all, &sys);
	// key press
	mlx_hook(sys.mlx.win, 2, 1L<<0, key_press, &sys);
	// key release
	mlx_hook(sys.mlx.win, 17, 1L << 17, end_simulation, &sys);
	mlx_hook(sys.mlx.win, 3, 1L<<1, key_release, &sys);
	mlx_hook(sys.mlx.win, 6, 1L << 6, mouse_move, &sys);
	mlx_loop(sys.mlx.mlx);
}

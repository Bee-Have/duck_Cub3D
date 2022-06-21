/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_routine_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:35:55 by amarini-          #+#    #+#             */
/*   Updated: 2022/06/21 20:21:13 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duckling3d_bonus.h"

void	mlx_routine(t_system sys)
{
	mlx_mouse_hide(sys.mlx.mlx, sys.mlx.win);
	mlx_loop_hook(sys.mlx.mlx, update_all, &sys);
	mlx_hook(sys.mlx.win, 2, 1L << 0, key_press, &sys);
	mlx_hook(sys.mlx.win, 17, 1L << 17, end_simulation, &sys);
	mlx_hook(sys.mlx.win, 3, 1L << 1, key_release, &sys);
	mlx_hook(sys.mlx.win, 6, 1L << 6, mouse_move, &sys);
	mlx_loop(sys.mlx.mlx);
}

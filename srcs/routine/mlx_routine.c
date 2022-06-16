/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_routine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:35:55 by amarini-          #+#    #+#             */
/*   Updated: 2022/06/14 20:55:27 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mlx_routine(t_system sys)
{
	mlx_loop_hook(sys.mlx.mlx, update_all, &sys);
	mlx_hook(sys.mlx.win, 2, 1L << 0, key_press, &sys);
	mlx_hook(sys.mlx.win, 3, 1L << 1, key_release, &sys);
	mlx_loop(sys.mlx.mlx);
}

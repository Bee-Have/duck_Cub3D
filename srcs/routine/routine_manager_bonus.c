/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_manager_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:03:57 by amarini-          #+#    #+#             */
/*   Updated: 2022/06/14 20:55:27 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	update_all(t_system *sys)
{
	update_keys_events(sys);
	raycasting_routine(sys);
	mlx_put_image_to_window(sys->mlx.mlx, sys->mlx.win, sys->mlx.img.img, 0, 0);
	minimap_routine(sys, T_LEFT);
	return (EXIT_SUCCESS);
}

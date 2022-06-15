/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_manager_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:03:57 by amarini-          #+#    #+#             */
/*   Updated: 2022/06/15 17:00:50 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	update_all(t_system *sys)
{
	update_keys_events(sys);
	raycasting_routine(sys);
	mlx_put_image_to_window(sys->mlx.mlx, sys->mlx.win, sys->mlx.img.img, 0, 0);
	// bonus
	minimap_routine(sys, T_LEFT);
	minimap_routine(sys, B_LEFT);
	minimap_routine(sys, T_RIGHT);
	minimap_routine(sys, B_RIGHT);
	return (EXIT_SUCCESS);
}

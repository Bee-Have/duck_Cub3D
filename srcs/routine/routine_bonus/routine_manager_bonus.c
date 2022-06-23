/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_manager_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:03:57 by amarini-          #+#    #+#             */
/*   Updated: 2022/06/22 19:59:30 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duckling3d_bonus.h"

int	update_all(t_system *sys)
{
	static int	map_pos = T_LEFT;

	if (sys->events.is_m_pressed == 1)
	{
		map_pos++;
		sys->events.is_m_pressed = 0;
		if (map_pos > CENTER)
			map_pos = T_LEFT;
	}
	update_keys_events(sys);
	if (map_pos == CENTER)
		map_routine(sys);
	else
	{
		raycasting_routine(sys);
		minimap_routine(sys, map_pos);
	}
	mlx_put_image_to_window(sys->mlx.mlx, sys->mlx.win, sys->mlx.img.img, 0, 0);
	return (EXIT_SUCCESS);
}

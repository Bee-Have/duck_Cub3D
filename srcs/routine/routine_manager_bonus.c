/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_manager_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:03:57 by amarini-          #+#    #+#             */
/*   Updated: 2022/06/15 18:04:28 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	update_all(t_system *sys)
{
	static int map_pos = T_LEFT;

	if (sys->events.is_m_pressed == 1)
	{
		map_pos++;
		sys->events.is_m_pressed = 0;
		if (map_pos > B_RIGHT)
			map_pos = T_LEFT;
	}
	update_keys_events(sys);
	raycasting_routine(sys);
	mlx_put_image_to_window(sys->mlx.mlx, sys->mlx.win, sys->mlx.img.img, 0, 0);
	minimap_routine(sys, map_pos);
	return (EXIT_SUCCESS);
}

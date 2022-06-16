/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_manager_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:03:57 by amarini-          #+#    #+#             */
/*   Updated: 2022/06/16 23:38:33 by amarini-         ###   ########.fr       */
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
		if (map_pos > B_RIGHT)
			map_pos = T_LEFT;
	}
	update_keys_events(sys);
	raycasting_routine(sys);
	mlx_put_image_to_window(sys->mlx.mlx, sys->mlx.win, sys->mlx.img.img, 0, 0);
	minimap_routine(sys, map_pos);
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_manager_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:03:57 by amarini-          #+#    #+#             */
/*   Updated: 2022/06/28 03:58:15 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duckling3d_bonus.h"

static void	fps_counter(t_system *sys)
{
	static time_t	previous_loop = 0;
	static int		frame = 0;
	static char		to_print[5];
	time_t			current_loop;

	frame++;
	current_loop = time(NULL);
	if (current_loop - previous_loop >= 1)
	{
		previous_loop = current_loop;
		ft_itoa_r(to_print, frame);
		frame = 0;
	}
	mlx_string_put(sys->mlx.mlx, sys->mlx.win,
		5, W_HEIGHT / 2, 0x00FFFFFF, to_print);
}

static void	enable_screenshot(t_system *sys)
{
	if (sys->events.is_f2_pressed == 1)
		mlx_string_put(sys->mlx.mlx, sys->mlx.win,
			W_WIDTH / 2, W_HEIGHT / 2, 0x00FFFFFF, "Taking a screen shot!");
	if (sys->events.is_f2_pressed == 1)
		sys->events.is_f2_pressed = 2;
}

int	update_all(t_system *sys)
{
	static int	map_pos = T_LEFT;

	if (sys->events.is_m_pressed == 1)
		if (++map_pos > CENTER)
			map_pos = T_LEFT;
	if (sys->events.is_m_pressed == 1)
		sys->events.is_m_pressed = 0;
	update_keys_events(sys);
	if (map_pos == CENTER)
		map_routine(sys);
	else
	{
		raycasting_routine(sys);
		minimap_routine(sys, map_pos);
	}
	if (sys->events.is_f2_pressed == 2)
		save_bmp(sys);
	mlx_put_image_to_window(sys->mlx.mlx, sys->mlx.win, sys->mlx.img.img, 0, 0);
	enable_screenshot(sys);
	fps_counter(sys);
	return (EXIT_SUCCESS);
}

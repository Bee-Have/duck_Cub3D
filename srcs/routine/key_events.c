/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:38:13 by amarini-          #+#    #+#             */
/*   Updated: 2022/05/30 17:05:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	key_press(int keycode, t_system *sys)
{
	//! ESC event will have to be more complete with free of malloced elems
	if (keycode == ESC)
		mlx_destroy_window(sys->mlx.mlx, sys->mlx.win);
	if (keycode == R_LEFT)
		sys->events.is_left_pressed = 1;
	else if (keycode == R_RIGHT)
		sys->events.is_right_pressed = 1;
	if (keycode == DOWN)
		sys->events.is_s_pressed = 1;
	if (keycode == UP)
		sys->events.is_w_pressed = 1;
	if (keycode == LEFT)
		sys->events.is_a_pressed = 1;
	if (keycode == RIGHT)
		sys->events.is_d_pressed = 1;
	return (EXIT_SUCCESS);
}

int	key_release(int keycode, t_system *sys)
{
	if (keycode == R_LEFT)
		sys->events.is_left_pressed = 0;
	else if (keycode == R_RIGHT)
		sys->events.is_right_pressed = 0;
	if (keycode == DOWN)
		sys->events.is_s_pressed = 0;
	if (keycode == UP)
		sys->events.is_w_pressed = 0;
	if (keycode == LEFT)
		sys->events.is_a_pressed = 0;
	if (keycode == RIGHT)
		sys->events.is_d_pressed = 0;
	return (EXIT_SUCCESS);
}

int	update_keys_events(t_system *sys)
{
	double	old_plane_x;

	if (sys->events.is_left_pressed == 1)
	{
		sys->pj.rot += R_SPEED;
		if (sys->pj.rot > 360)
			sys->pj.rot = 0 + (sys->pj.rot - 360);
		old_plane_x = sys->pj.plane.x;
		sys->pj.plane.x = sys->pj.plane.x * cos(R_SPEED * (M_PI / 180)) - sys->pj.plane.y * sin(R_SPEED * (M_PI / 180));
		sys->pj.plane.y = old_plane_x * sin(R_SPEED * (M_PI / 180)) + sys->pj.plane.y * cos(R_SPEED * (M_PI / 180));
	}
	if (sys->events.is_right_pressed == 1)
	{
		sys->pj.rot -= R_SPEED;
		if (sys->pj.rot < 0)
			sys->pj.rot = 360 - (sys->pj.rot * -1);
		old_plane_x = sys->pj.plane.x;
		sys->pj.plane.x = sys->pj.plane.x * cos(-R_SPEED * (M_PI / 180)) - sys->pj.plane.y * sin(-R_SPEED * (M_PI / 180));
		sys->pj.plane.y = old_plane_x * sin(-R_SPEED * (M_PI / 180)) + sys->pj.plane.y * cos(-R_SPEED * (M_PI / 180));
	}
	if (sys->events.is_s_pressed == 1)
	{
		sys->pj.pos.x += (SPEED * cosf(sys->pj.rot * (M_PI / 180)));
		sys->pj.pos.y += (SPEED * sinf(sys->pj.rot * (M_PI / 180)));
	}
	if (sys->events.is_w_pressed == 1)
	{
		sys->pj.pos.x -= (SPEED * cosf(sys->pj.rot * (M_PI / 180)));
		sys->pj.pos.y -= (SPEED * sinf(sys->pj.rot * (M_PI / 180)));
	}
	if (sys->events.is_a_pressed == 1)
	{
		sys->pj.pos.x += (SPEED * cosf((sys->pj.rot - 90) * (M_PI / 180)));
		sys->pj.pos.y += (SPEED * sinf((sys->pj.rot - 90) * (M_PI / 180)));
	}
	if (sys->events.is_d_pressed == 1)
	{
		sys->pj.pos.x += (SPEED * cosf((sys->pj.rot + 90) * (M_PI / 180)));
		sys->pj.pos.y += (SPEED * sinf((sys->pj.rot + 90) * (M_PI / 180)));
	}
	sys->pj.dir.x = sys->pj.pos.x - (SPEED * cosf(sys->pj.rot * (M_PI / 180)));
	sys->pj.dir.y = sys->pj.pos.y - (SPEED * sinf(sys->pj.rot * (M_PI / 180)));
	return (EXIT_SUCCESS);
}

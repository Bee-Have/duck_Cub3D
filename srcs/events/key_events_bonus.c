/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:38:13 by amarini-          #+#    #+#             */
/*   Updated: 2022/06/21 14:27:34 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int keycode, t_system *sys)
{
	if (keycode == ESC)
		end_simulation(sys, EXIT_SUCCESS);
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
	if (keycode == M)
		sys->events.is_m_pressed = 1;
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

static void	move_player(t_system *sys, char c_dir)
{
	t_vec2	dir;

	if (c_dir == 'W')
		dir = make_vec2(sys->pj.pos.y + (sys->pj.dir.y * DIR * SPEED),
				sys->pj.pos.x + (sys->pj.dir.x * DIR * SPEED));
	else if (c_dir == 'S')
		dir = make_vec2(sys->pj.pos.y - (sys->pj.dir.y * DIR * SPEED),
				sys->pj.pos.x - (sys->pj.dir.x * DIR * SPEED));
	else if (c_dir == 'A')
		dir = make_vec2(sys->pj.pos.y + ((sys->pj.dir.x * sin(M_PI * 3 / 2)
						+ sys->pj.dir.y * cos(M_PI * 3 / 2)) * DIR * SPEED),
				sys->pj.pos.x + ((sys->pj.dir.x * cos(M_PI * 3 / 2)
						- sys->pj.dir.y * sin(M_PI * 3 / 2)) * DIR * SPEED));
	else
		dir = make_vec2(sys->pj.pos.y + ((sys->pj.dir.x * sin(M_PI_2)
						+ sys->pj.dir.y * cos(M_PI_2)) * DIR * SPEED),
				sys->pj.pos.x + ((sys->pj.dir.x * cos(M_PI_2) - sys->pj.dir.y
						* sin(M_PI_2)) * DIR * SPEED));
	if (dir.x > 0 && dir.x < ft_strlen(sys->s_i.map[(int)sys->pj.pos.y]))
		sys->pj.pos.x = dir.x;
	if (dir.y > 0 && dir.y < ft_tab_len((void **)sys->s_i.map))
		sys->pj.pos.y = dir.y;
}

void	rotate_player(t_system *sys, char dir, double speed)
{
	if (dir == 'R')
	{
		sys->pj.dir = make_vec2(sys->pj.dir.x * sin(speed)
				+ sys->pj.dir.y * cos(speed), sys->pj.dir.x * cos(speed)
				- sys->pj.dir.y * sin(speed));
		sys->pj.plane = make_vec2(sys->pj.plane.x * sin(speed)
				+ sys->pj.plane.y * cos(speed),
				sys->pj.plane.x * cos(speed)
				- sys->pj.plane.y * sin(speed));
	}
	else if (dir == 'L')
	{
		sys->pj.dir = make_vec2(sys->pj.dir.x * sin(-speed)
				+ sys->pj.dir.y * cos(-speed), sys->pj.dir.x * cos(-speed)
				- sys->pj.dir.y * sin(-speed));
		sys->pj.plane = make_vec2(sys->pj.plane.x * sin(-speed)
				+ sys->pj.plane.y * cos(-speed),
				sys->pj.plane.x * cos(-speed)
				- sys->pj.plane.y * sin(-speed));
	}
}

int	update_keys_events(t_system *sys)
{
	if (sys->events.is_left_pressed == 1)
		rotate_player(sys, 'L', R_SPEED);
	if (sys->events.is_right_pressed == 1)
		rotate_player(sys, 'R', R_SPEED);
	if (sys->events.is_w_pressed == 1)
		move_player(sys, 'W');
	if (sys->events.is_s_pressed == 1)
		move_player(sys, 'S');
	if (sys->events.is_a_pressed == 1)
		move_player(sys, 'A');
	if (sys->events.is_d_pressed == 1)
		move_player(sys, 'D');
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:38:13 by amarini-          #+#    #+#             */
/*   Updated: 2022/06/06 15:48:12 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
		dir = make_vec2(sys->pj.pos.y + (sys->pj.dir.y * SPEED * 6),
				sys->pj.pos.x + (sys->pj.dir.x * SPEED * 6));
	else if (c_dir == 'S')
		dir = make_vec2(sys->pj.pos.y - (sys->pj.dir.y * SPEED * 6),
				sys->pj.pos.x - (sys->pj.dir.x * SPEED * 6));
	else if (c_dir == 'A')
		dir = make_vec2(sys->pj.pos.y + ((sys->pj.dir.x * sin(M_PI * 3 / 2)
						+ sys->pj.dir.y * cos(M_PI * 3 / 2)) * SPEED * 6),
				sys->pj.pos.x + ((sys->pj.dir.x * cos(M_PI * 3 / 2)
						- sys->pj.dir.y * sin(M_PI * 3 / 2)) * SPEED * 6));
	else
		dir = make_vec2(sys->pj.pos.y + ((sys->pj.dir.x * sin(M_PI_2)
						+ sys->pj.dir.y * cos(M_PI_2)) * SPEED * 6),
				sys->pj.pos.x + ((sys->pj.dir.x * cos(M_PI_2) - sys->pj.dir.y
						* sin(M_PI_2)) * SPEED * 6));
	if (dir.x > 0 && dir.x < ft_strlen(sys->s_i.map[(int)sys->pj.pos.y]))
		sys->pj.pos.x = dir.x;
	if (dir.y > 0 && dir.y < ft_tab_len((void **)sys->s_i.map))
		sys->pj.pos.y = dir.y;
}

static void	rotate_player(t_system *sys, char dir)
{
	if (dir == 'R')
	{
		sys->pj.dir = make_vec2(sys->pj.dir.x * sin(R_SPEED)
				+ sys->pj.dir.y * cos(R_SPEED), sys->pj.dir.x * cos(R_SPEED)
				- sys->pj.dir.y * sin(R_SPEED));
		sys->pj.plane = make_vec2(sys->pj.plane.x * sin(R_SPEED)
				+ sys->pj.plane.y * cos(R_SPEED),
				sys->pj.plane.x * cos(R_SPEED)
				- sys->pj.plane.y * sin(R_SPEED));
	}
	else if (dir == 'L')
	{
		sys->pj.dir = make_vec2(sys->pj.dir.x * sin(-R_SPEED)
				+ sys->pj.dir.y * cos(-R_SPEED), sys->pj.dir.x * cos(-R_SPEED)
				- sys->pj.dir.y * sin(-R_SPEED));
		sys->pj.plane = make_vec2(sys->pj.plane.x * sin(-R_SPEED)
				+ sys->pj.plane.y * cos(-R_SPEED),
				sys->pj.plane.x * cos(-R_SPEED)
				- sys->pj.plane.y * sin(-R_SPEED));
	}
}

int	update_keys_events(t_system *sys)
{
	if (sys->events.is_left_pressed == 1)
		rotate_player(sys, 'L');
	if (sys->events.is_right_pressed == 1)
		rotate_player(sys, 'R');
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

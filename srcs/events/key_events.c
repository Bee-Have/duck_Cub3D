/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:38:13 by amarini-          #+#    #+#             */
/*   Updated: 2022/06/04 13:14:31 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#define TO_DEG * (M_PI / 180)

int	key_press(int keycode, t_system *sys)
{
	if (keycode == ESC)
		end_simulation(sys);
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

static void	move_player(t_system *sys, t_vec2 dir)
{
	t_vec2	a_p;
	t_vec2	n_p;

	a_p = sys->pj.pos;
	n_p = make_vec2(a_p.y + dir.y, a_p.x + dir.x);
	if (n_p.x > 0 && n_p.x < ft_strlen(sys->s_i.map[(int)a_p.y]))
		sys->pj.pos.x = n_p.x;
	if (n_p.y > 0 && n_p.y < ft_tab_len((void **)sys->s_i.map))
		sys->pj.pos.y = n_p.y;
}

static void	rotate_player(t_system *sys, char dir)
{
	double	old_plane_x;

	if (dir == 'L')
	{
		sys->pj.rot += R_SPEED;
		if (sys->pj.rot > 360)
			sys->pj.rot = 0 + (sys->pj.rot - 360);
		old_plane_x = sys->pj.plane.x;
		sys->pj.plane.x = sys->pj.plane.x * cos(R_SPEED TO_DEG)
			- sys->pj.plane.y * sin(R_SPEED TO_DEG);
		sys->pj.plane.y = old_plane_x * sin(R_SPEED TO_DEG)
			+ sys->pj.plane.y * cos(R_SPEED TO_DEG);
	}
	else if (dir == 'R')
	{
		sys->pj.rot -= R_SPEED;
		if (sys->pj.rot < 0)
			sys->pj.rot = 360 - (sys->pj.rot * -1);
		old_plane_x = sys->pj.plane.x;
		sys->pj.plane.x = sys->pj.plane.x * cos(-R_SPEED TO_DEG)
			- sys->pj.plane.y * sin(-R_SPEED TO_DEG);
		sys->pj.plane.y = old_plane_x * sin(-R_SPEED TO_DEG)
			+ sys->pj.plane.y * cos(-R_SPEED TO_DEG);
	}
}

int	update_keys_events(t_system *sys)
{
	if (sys->events.is_left_pressed == 1)
		rotate_player(sys, 'R');
	if (sys->events.is_right_pressed == 1)
		rotate_player(sys, 'L');
	if (sys->events.is_s_pressed == 1)
		move_player(sys, make_vec2((SPEED * sinf(sys->pj.rot TO_DEG)),
				(SPEED * cosf(sys->pj.rot TO_DEG))));
	if (sys->events.is_w_pressed == 1)
		move_player(sys, make_vec2(-(SPEED * sinf(sys->pj.rot TO_DEG)),
				-(SPEED * cosf(sys->pj.rot TO_DEG))));
	if (sys->events.is_a_pressed == 1)
		move_player(sys, make_vec2((SPEED * sinf((sys->pj.rot + 90) TO_DEG)),
				(SPEED * cosf((sys->pj.rot + 90) TO_DEG))));
	if (sys->events.is_d_pressed == 1)
		move_player(sys, make_vec2((SPEED * sinf((sys->pj.rot - 90) TO_DEG)),
				(SPEED * cosf((sys->pj.rot - 90) TO_DEG))));
	sys->pj.dir.x = sys->pj.pos.x - (SPEED * cosf(sys->pj.rot TO_DEG));
	sys->pj.dir.y = sys->pj.pos.y - (SPEED * sinf(sys->pj.rot TO_DEG));
	return (EXIT_SUCCESS);
}

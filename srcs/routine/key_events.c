/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:38:13 by amarini-          #+#    #+#             */
/*   Updated: 2022/05/17 16:08:27 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	key_press(int keycode, t_mlx *mlx)
{
	//! ESC event will have to be more complete with free of malloced elems
	if (keycode == ESC)
		mlx_destroy_window(mlx->mlx, mlx->win);
	if (keycode == R_LEFT)
		mlx->event.is_left_pressed = 1;
	else if (keycode == R_RIGHT)
		mlx->event.is_right_pressed = 1;
	if (keycode == DOWN)
		mlx->event.is_s_pressed = 1;
	if (keycode == UP)
		mlx->event.is_w_pressed = 1;
	if (keycode == LEFT)
		mlx->event.is_a_pressed = 1;
	if (keycode == RIGHT)
		mlx->event.is_d_pressed = 1;
	return (EXIT_SUCCESS);
}

int	key_release(int keycode, t_mlx *mlx)
{
	if (keycode == R_LEFT)
		mlx->event.is_left_pressed = 0;
	else if (keycode == R_RIGHT)
		mlx->event.is_right_pressed = 0;
	if (keycode == DOWN)
		mlx->event.is_s_pressed = 0;
	if (keycode == UP)
		mlx->event.is_w_pressed = 0;
	if (keycode == LEFT)
		mlx->event.is_a_pressed = 0;
	if (keycode == RIGHT)
		mlx->event.is_d_pressed = 0;
	return (EXIT_SUCCESS);
}

int	update_keys_events(t_mlx *mlx)
{
	if (mlx->event.is_left_pressed == 1)
	{
		mlx->pj.rot -= R_SPEED;
		if (mlx->pj.rot < 0)
			mlx->pj.rot = 360 - (mlx->pj.rot * -1);
	}
	if (mlx->event.is_right_pressed == 1)
	{
		mlx->pj.rot += R_SPEED;
		if (mlx->pj.rot > 360)
			mlx->pj.rot = 0 + (mlx->pj.rot - 360);
	}
	if (mlx->event.is_s_pressed == 1)
	{
		mlx->pj.pos.x += (SPEED * cosf(mlx->pj.rot * (M_PI / 180)));
		mlx->pj.pos.y += (SPEED * sinf(mlx->pj.rot * (M_PI / 180)));
	}
	if (mlx->event.is_w_pressed == 1)
	{
		mlx->pj.pos.x -= (SPEED * cosf(mlx->pj.rot * (M_PI / 180)));
		mlx->pj.pos.y -= (SPEED * sinf(mlx->pj.rot * (M_PI / 180)));
	}
	if (mlx->event.is_a_pressed == 1)
	{
		mlx->pj.pos.x += (SPEED * cosf((mlx->pj.rot + 90) * (M_PI / 180)));
		mlx->pj.pos.y += (SPEED * sinf((mlx->pj.rot + 90) * (M_PI / 180)));
	}
	if (mlx->event.is_d_pressed == 1)
	{
		mlx->pj.pos.x += (SPEED * cosf((mlx->pj.rot - 90) * (M_PI / 180)));
		mlx->pj.pos.y += (SPEED * sinf((mlx->pj.rot - 90) * (M_PI / 180)));
	}
	return (EXIT_SUCCESS);
}

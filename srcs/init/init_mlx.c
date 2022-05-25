/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 18:09:36 by amarini-          #+#    #+#             */
/*   Updated: 2022/05/25 17:06:30 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_img	init_img(void)
{
	t_img	img;
	img.path = NULL;
	img.img = NULL;
	img.addr = NULL;
	img.bits_pxl = 0;
	img.line_len = 0;
	img.endian = 0;
	return (img);
}

t_event	init_events(void)
{
	t_event	events;

	events.is_w_pressed = 0;
	events.is_a_pressed = 0;
	events.is_s_pressed = 0;
	events.is_d_pressed = 0;
	events.is_left_pressed = 0;
	events.is_right_pressed = 0;
	return (events);
}

t_mlx	init_mlx(int width, int height)
{
	t_mlx	mlx;

	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, width, height, "cub3D");
	mlx.img = init_img();
	mlx.img.img = mlx_new_image(mlx.mlx, width, height);
	mlx.img.addr = mlx_get_data_addr(mlx.img.img, &mlx.img.bits_pxl
								, &mlx.img.line_len, &mlx.img.endian);
	return (mlx);
}

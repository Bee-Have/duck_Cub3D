/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 18:09:36 by amarini-          #+#    #+#             */
/*   Updated: 2022/05/17 15:35:02 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_img	init_img(void)
{
	t_img	img;
	img.addr = NULL;
	img.bits_pxl = 0;
	img.line_len = 0;
	img.endian = 0;
	return (img);
}

static void	init_events(t_mlx *mlx)
{
	mlx->event.is_w_pressed = 0;
	mlx->event.is_a_pressed = 0;
	mlx->event.is_s_pressed = 0;
	mlx->event.is_d_pressed = 0;
	mlx->event.is_left_pressed = 0;
	mlx->event.is_right_pressed = 0;
	return ;
}

t_mlx	*init_mlx(int width, int height)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	//send error if pb w/ malloc
	if (!mlx)
		return (NULL);
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, width, height, "cub3D");
	mlx->img = init_img();
	mlx->img.img = mlx_new_image(mlx->mlx, width, height);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bits_pxl
								, &mlx->img.line_len, &mlx->img.endian);
	mlx->screen.x = width;
	mlx->screen.y = height;
	init_events(mlx);
	mlx->map = NULL;
	return (mlx);
}

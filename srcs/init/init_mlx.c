/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 18:09:36 by amarini-          #+#    #+#             */
/*   Updated: 2022/06/28 04:54:08 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	init_img(void)
{
	t_img	img;

	img.img = NULL;
	img.addr = NULL;
	img.bits_pxl = 0;
	img.line_len = 0;
	img.endian = 0;
	return (img);
}

t_mlx	init_mlx(char window_name[10])
{
	t_mlx	mlx;

	mlx.mlx = mlx_init();
	if (mlx.mlx == NULL)
	{
		ft_putstr_fd(2, "Error\nUnable to init mlx\n");
		exit(1);
	}
	mlx.win = mlx_new_window(mlx.mlx, W_WIDTH, W_HEIGHT, window_name);
	if (mlx.win == NULL)
	{
		ft_putstr_fd(2, "Error\nUnable to create a window\n");
		exit(1);
	}
	mlx.img = init_img();
	mlx.img.img = mlx_new_image(mlx.mlx, W_WIDTH, W_HEIGHT);
	mlx.img.addr = mlx_get_data_addr(mlx.img.img, &mlx.img.bits_pxl,
			&mlx.img.line_len, &mlx.img.endian);
	return (mlx);
}

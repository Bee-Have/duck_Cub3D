/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx_managment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 14:36:42 by amarini-          #+#    #+#             */
/*   Updated: 2021/04/29 17:20:30 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3D.h"

void	init_minilibx(t_cub **list)
{
	t_vars	*vars;
	t_data	*img;

	vars = init_mlx_vars();
	img = init_mlx_data();
	vars->mlx_win = mlx_new_window(vars->mlx, (*list)->res->width, (*list)->res->height, "cub3D");
	img->img = mlx_new_image(vars->mlx, (*list)->res->width, (*list)->res->height);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pix, &img->line_length,
								&img->endian);
	//my_mlx_pxl_put(&img, 5, 5, 0x00FF0000);
	test_pxl_loop(&img, &vars);
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, img->img, 0, 0);
	//mlx_key_hook(vars->mlx_win, key_hook, &vars);
	mlx_loop(vars->mlx);
}

//dis is mine and just for funny testing
void	test_pxl_loop(t_data **data, t_vars **vars)
{
	int	original_x;
	int	x;
	int	y;
	int	gradiant;
	int	max;
	int	color_1;
	int	color_2;

	original_x = 960;
	x = original_x;
	y = 5;
	gradiant = 960;
	max = 1080;
	color_1 = 0x00FFFF00;
	color_2 = 0x00FF00FF;
	while (y < max)
	{
		while(x <= gradiant)
		{
			if (x <= 960)
				my_mlx_pxl_put(data, x, y, color_1);
			else
				my_mlx_pxl_put(data, x, y, color_2);
			 color_1--;
			 color_2--;
			x++;
		}
		if (y < 540 && gradiant <= (960 + 480))
		{
			gradiant += 1;
			original_x -= 1;
		}
		else
		{
			gradiant -= 1;
			original_x += 1;
		}
		x = original_x;
		// color_1 = 0x00FFFFFF;
		// color_2 = 0x00FF0000;
		 color_1--;
		 color_2--;
		y++;
	}
}

void	my_mlx_pxl_put(t_data **data, int x, int y, int color)
{
	char	*dst;

	dst = (*data)->addr + (y * (*data)->line_length + x *((*data)->bits_per_pix / 8));
	*(unsigned int *)dst = color;
}

int		key_hook(int keycode, t_vars **vars)
{
	printf("hello from key_hook\n");
}

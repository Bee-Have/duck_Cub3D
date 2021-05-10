/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx_managment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 14:36:42 by amarini-          #+#    #+#             */
/*   Updated: 2021/05/10 17:07:02 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3D.h"

void	init_minilibx(t_cub **list)
{
	//t_all	*all;
	t_vars	*vars;
	t_data	*img;

	//all = init_all();
	vars = init_mlx_vars();
	img = init_mlx_data();
	//all->cub = (*list);
	//all->vars = vars;
	//all->data = img;
	vars->mlx_win = mlx_new_window(vars->mlx, (*list)->res->width, (*list)->res->height, "cub3D");
	img->img = mlx_new_image(vars->mlx, (*list)->res->width, (*list)->res->height);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pix, &img->line_length,
								&img->endian);
	//test_pxl_loop(&img);
	//print_map((*list)->map);
	test_print_map((*list), &img);
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, img->img, 0, 0);
	mlx_key_hook(vars->mlx_win, key_hook, &vars);
	mlx_hook(vars->mlx_win, 17, 1L<<2, close_window, &vars);
	//mlx_hook(vars->mlx_win, 06, 1L<<6, mouse_in_window, &vars);
	mlx_mouse_hook(vars->mlx_win, mouse_hook, &vars);
	//mlx_expose_hook(vars->mlx_win, window_hook, &vars);
	mlx_loop_hook(vars->mlx, test_print_map, &vars);
	mlx_loop(vars->mlx);
}

int		test_render_next_frame(t_all **list)
{
	
}

//dis is mine and just for funny testing
void	test_print_map(t_cub *cub, t_data **data)
{
	int		i;
	int		j;
	int		max_x;
	int		max_y;
	int		x;
	int		y;

	i = 0;
	j = 0;
	max_x = 0;
	max_y = 0;
	x = 100;
	y = 100;
	while (cub->map[j] != NULL)
	{
		while (cub->map[j][i] != '\0')
		{
			if (cub->map[j][i] == '0')
				my_mlx_pxl_put(data, x, y, 0x00FF7F7F);
			else if (cub->map[j][i] == '1')
				my_mlx_pxl_put(data, x, y, 0x00FFFFFF);
			else if (str_cmp(cub->map[j][i], NULL, "NSEW") == 1)
				my_mlx_pxl_put(data, x, y, 0x00FFFF00);
			else
				my_mlx_pxl_put(data, x, y, 0x007F7F7F);
			if (max_x < 15)
				max_x++;
			else
			{
				max_x = 0;
				i++;
			}
				x++;
		}
		while (i < cub->longest_map)
		{
			my_mlx_pxl_put(data, x, y, 0x007F7F7F);
			if (max_x < 15)
				max_x++;
			else
			{
				max_x = 0;
				i++;
			}
				x++;
		}
		i = 0;
		x = 100;
		if (max_y < 15)
			max_y++;
		else
		{
			max_y = 0;
			j++;
		}
			y++;
	}
}

//dis is mine and just for funny testing
void	test_pxl_loop(t_data **data/*, t_vars **vars*/)
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

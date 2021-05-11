/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_printing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:19:25 by amarini-          #+#    #+#             */
/*   Updated: 2021/05/11 17:32:06 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3D.h"

//dis old, gonna build a new more functioning one
//don't really need to though so in the end i won't since printing
//the map from top is not needed for now
//just deal with moving your goddamn player idiot
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

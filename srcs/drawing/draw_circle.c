/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_circle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:15:33 by amarini-          #+#    #+#             */
/*   Updated: 2022/05/16 16:15:46 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_circle(t_mlx *mlx, t_color color, t_vec2 pos, int size)
{
	t_vec2	check;
	t_vec2	center;
	float	dist;
	int		x;

	center.x = pos.x + size / 2;
	center.y = pos.y + size / 2;
	x = pos.x;
	check.y = 0;
	while (pos.y < 1080 && check.y < size)
	{
		pos.x = x;
		check.x = 0;
		while (pos.x < 1920 && check.x < size)
		{
			dist = sqrt((pos.x - center.x) * (pos.x - center.x) +
						(pos.y - center.y) * (pos.y - center.y));
			if (dist < size / 2)
				draw_pxl(mlx, pos, color);
			++pos.x;
			++check.x;
		}
		++pos.y;
		++check.y;
	}
}
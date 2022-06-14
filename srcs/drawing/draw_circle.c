/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_circle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:15:33 by amarini-          #+#    #+#             */
/*   Updated: 2022/06/14 20:55:27 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_circle(t_system *sys, t_color color, t_int2 pos, int size)
{
	t_int2	check;
	t_int2	center;
	float	dist;
	int		x;

	center = make_int2(pos.y + size / 2, pos.x + size / 2);
	x = pos.x;
	check = make_int2(0, 0);
	while (pos.y < 1080 && check.y < size)
	{
		pos.x = x;
		check.x = 0;
		while (pos.x < 1920 && check.x < size)
		{
			dist = sqrt((pos.x - center.x) * (pos.x - center.x)
					+ (pos.y - center.y) * (pos.y - center.y));
			if (dist < size / 2)
				draw_pxl(sys, pos, color);
			++pos.x;
			++check.x;
		}
		++pos.y;
		++check.y;
	}
}

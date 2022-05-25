/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_square.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:16:27 by amarini-          #+#    #+#             */
/*   Updated: 2022/05/25 17:55:45 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_square(t_system *sys, t_color color, t_int2 pos, int size)
{
	int		x;
	t_int2	check;

	x = pos.x;
	check.y = 0;
	while (pos.y < 1080 && check.y < size)
	{
		pos.x = x;
		check.x = 0;
		while (pos.x < 1920 && check.x < size)
		{
			draw_pxl(sys, pos, color);
			++pos.x;
			++check.x;
		}
		++pos.y;
		++check.y;
	}
}


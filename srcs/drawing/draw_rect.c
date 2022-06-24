/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:16:27 by amarini-          #+#    #+#             */
/*   Updated: 2022/06/22 20:31:55 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_rect(t_system *sys, t_color color, t_int2 pos, t_int2 size)
{
	int		x;
	t_int2	check;

	x = pos.x;
	check = make_int2(0, 0);
	while (pos.y < 1080 && check.y < size.y)
	{
		pos.x = x;
		check.x = 0;
		while (pos.x < 1920 && check.x < size.x)
		{
			draw_pxl(sys, pos, color);
			++pos.x;
			++check.x;
		}
		++pos.y;
		++check.y;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:13:42 by amarini-          #+#    #+#             */
/*   Updated: 2022/06/14 20:55:27 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	switch_vec2(t_int2 *vector)
{
	int	tmp;

	tmp = (*vector).x;
	(*vector).x = (*vector).y;
	(*vector).y = tmp;
}

//m = slope
//d = decide
static void	plot_pxl(t_system *sys, t_int4 limits, t_int2 m, int decide,
				t_color color)
{
	int		err;
	int		i;
	int		len;

	err = 2 * m.y - m.x;
	len = 1;
	i = 0;
	while (i < m.x)
	{
		if (limits.start.x < limits.end.x)
			++limits.start.x;
		else
			--limits.start.x;
		if (err < 0)
		{
			if (decide == 1)
			{
				switch_vec2(&limits.start);
				draw_square(sys, color, limits.start, len);
				switch_vec2(&limits.start);
			}
			else
				draw_square(sys, color, limits.start, len);
			err = err + 2 * m.y;
		}
		else
		{
			if (limits.start.y < limits.end.y)
				++limits.start.y;
			else
				--limits.start.y;
			if (decide == 1)
			{
				switch_vec2(&limits.start);
				draw_square(sys, color, limits.start, len);
				switch_vec2(&limits.start);
			}
			else
				draw_square(sys, color, limits.start, len);
			err = err + 2 * m.y - 2 * m.x;
		}
		++i;
	}
}

//m = slope
void	draw_line(t_system *sys, t_int2 start, t_int2 end, t_color color)
{
	t_int2	m;
	t_int4	limits;

	m = make_int2(abs(end.y - start.y), abs(end.x - start.x));
	limits.start = start;
	limits.end = end;
	if (m.x < m.y)
	{
		switch_vec2(&limits.start);
		switch_vec2(&limits.end);
		switch_vec2(&m);
		plot_pxl(sys, limits, m, 1, color);
	}
	else
		plot_pxl(sys, limits, m, 0, color);
}

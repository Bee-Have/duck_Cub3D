/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:13:42 by amarini-          #+#    #+#             */
/*   Updated: 2022/05/29 14:38:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	switch_vec2(t_int2 *vector)
{
	int	tmp;

	tmp = (*vector).x;
	(*vector).x = (*vector).y;
	(*vector).y = tmp;
}

//m = slope
void	plot_pxl(t_system *sys, t_int2 start, t_int2 end, t_int2 m, int decide, t_color color)
{
	int		err;
	int		i;
	int		len;

	err = 2 * m.y - m.x;
	len = 1;
	i = 0;
	while (i < m.x)
	{
		if (start.x < end.x)
			++start.x;
		else
			--start.x;
		if (err < 0)
		{
			if (decide == 1)
			{
				switch_vec2(&start);
				draw_square(sys, color, start, len);
				switch_vec2(&start);
			}
			else
				draw_square(sys, color, start, len);
			err = err + 2 * m.y;
		}
		else
		{
			if (start.y < end.y)
				++start.y;
			else
				--start.y;
			if (decide == 1)
			{
				switch_vec2(&start);
				draw_square(sys, color, start, len);
				switch_vec2(&start);
			}
			else
				draw_square(sys, color, start, len);
			err = err + 2 * m.y - 2 * m.x;
		}
		++i;
	}
}

//m = slope
void	draw_line(t_system *sys, t_int2 start, t_int2 end, t_color color)
{
	t_int2	m;

	m = make_int2(abs(end.y - start.y), abs(end.x - start.x));
	if (m.x < m.y)
	{
		switch_vec2(&start);
		switch_vec2(&end);
		switch_vec2(&m);
		plot_pxl(sys, start, end, m, 1, color);
	}
	else
		plot_pxl(sys, start, end, m, 0, color);
}


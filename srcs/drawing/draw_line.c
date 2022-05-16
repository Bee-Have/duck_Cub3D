/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:13:42 by amarini-          #+#    #+#             */
/*   Updated: 2022/05/16 16:14:32 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	switch_vec2(t_vec2 *vector)
{
	int	tmp;

	tmp = (*vector).x;
	(*vector).x = (*vector).y;
	(*vector).y = tmp;
}

//m = slope
void	plot_pxl(t_mlx *mlx, t_vec2 start, t_vec2 end, t_vec2 m, int decide)
{
	t_color	color;
	int		err;
	int		i;
	int		len;

	color = make_color(255, 0, 255, 0);
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
				draw_square(mlx, color, start, len);
				switch_vec2(&start);
			}
			else
				draw_square(mlx, color, start, len);
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
				draw_square(mlx, color, start, len);
				switch_vec2(&start);
			}
			else
				draw_square(mlx, color, start, len);
			err = err + 2 * m.y - 2 * m.x;
		}
		++i;
	}
}

//m = slope
void	draw_line(t_mlx *mlx, t_vec2 start, t_vec2 end)
{
	int		dx;
	int		dy;
	t_vec2	m;

	dx = abs(end.x - start.x);
	dy = abs(end.y - start.y);
	m.x = dx;
	m.y = dy;
	if (dx < dy)
	{
		switch_vec2(&start);
		switch_vec2(&end);
		switch_vec2(&m);
		plot_pxl(mlx, start, end, m, 1);
	}
	else
		plot_pxl(mlx, start, end, m, 0);
}


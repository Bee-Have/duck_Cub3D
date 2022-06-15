/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:13:42 by amarini-          #+#    #+#             */
/*   Updated: 2022/06/15 17:43:41 by user42           ###   ########.fr       */
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

static void	switch_draw(t_system *sys, t_line_info info, t_color color)
{
	if (info.decide == 1)
	{
		switch_vec2(&info.start);
		draw_pxl(sys, info.start, color);
		switch_vec2(&info.start);
	}
	else
		draw_pxl(sys, info.start, color);
}

//m = slope
static void	plot_pxl(t_system *sys, t_line_info info, t_color color)
{
	int		i;

	i = 0;
	while (i < info.m.x)
	{
		if (info.start.x < info.end.x)
			++info.start.x;
		else
			--info.start.x;
		if (info.err < 0)
		{
			switch_draw(sys, info, color);
			info.err = info.err + 2 * info.m.y;
		}
		else
		{
			if (info.start.y < info.end.y)
				++info.start.y;
			else
				--info.start.y;
			switch_draw(sys, info, color);
			info.err = info.err + 2 * info.m.y - 2 * info.m.x;
		}
		++i;
	}
}

//m = slope
void	draw_line(t_system *sys, t_int2 start, t_int2 end, t_color color)
{
	t_line_info	info;

	info.m = make_int2(abs(end.y - start.y), abs(end.x - start.x));
	info.start = start;
	info.end = end;
	info.decide = 0;
	if (info.m.x < info.m.y)
	{
		switch_vec2(&info.start);
		switch_vec2(&info.end);
		switch_vec2(&info.m);
		info.decide = 1;
	}
	info.err = 2 * info.m.y - info.m.x;
	plot_pxl(sys, info, color);
}

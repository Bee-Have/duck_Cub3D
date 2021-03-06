/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 19:57:20 by ldutriez          #+#    #+#             */
/*   Updated: 2022/06/24 18:28:43 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duckling3d_bonus.h"

static int	map_pxl_unit(t_system * sys)
{
	t_int2	pxl_unit;

	pxl_unit.x = W_WIDTH / sys->s_i.map_width;
	pxl_unit.y = W_HEIGHT / sys->s_i.map_height;
	if (pxl_unit.x < pxl_unit.y)
		return (pxl_unit.x);
	return (pxl_unit.y);
}

static void	render_map(t_system *sys, t_int2 pos)
{
	t_color	color;
	t_int2	imap;
	int		xaddr;

	xaddr = pos.x;
	imap = make_int2(0, 0);
	while (sys->s_i.map[imap.y] != NULL)
	{
		imap.x = 0;
		pos.x = xaddr;
		while (sys->s_i.map[imap.y][imap.x] != '\0')
		{
			if (sys->s_i.map[imap.y][imap.x] == '0')
				color = make_color(255, 255, 255, 255);
			if (sys->s_i.map[imap.y][imap.x] == '1')
				color = make_color(255, 0, 128, 255);
			if (sys->s_i.map[imap.y][imap.x] == '0'
				|| sys->s_i.map[imap.y][imap.x] == '1')
				draw_square(sys, color, pos, sys->s_i.pxl_unit);
			pos.x += sys->s_i.pxl_unit;
			++imap.x;
		}
		pos.y += sys->s_i.pxl_unit;
		++imap.y;
	}
}

void	render_pj(t_system *sys, t_int2 map_start)
{
	t_color	color;
	t_int2	pos;
	t_int2	dir;
	t_int2	middle;
	int		size;

	size = sys->s_i.pxl_unit / 2;
	if (size < 10)
		size = sys->s_i.pxl_unit;
	color = make_color(255, 255, 0, 0);
	pos.x = (map_start.x + (sys->pj.pos.x * sys->s_i.pxl_unit) - size / 2);
	pos.y = (map_start.y + (sys->pj.pos.y * sys->s_i.pxl_unit) - size / 2);
	draw_circle(sys, color, pos, size);
	middle = make_int2(pos.y + size / 2, pos.x + size / 2);
	dir.y = sys->pj.dir.y * sys->s_i.pxl_unit * 2 + middle.y;
	dir.x = sys->pj.dir.x * sys->s_i.pxl_unit * 2 + middle.x;
	color = make_color(255, 0, 255, 0);
	draw_line(sys, middle, dir, color);
}

void	map_routine(t_system *sys)
{
	t_int2	map_size;
	t_int2	offset;

	if (sys->s_i.pxl_unit == 0)
		sys->s_i.pxl_unit = map_pxl_unit(sys);
	map_size.x = sys->s_i.map_width * sys->s_i.pxl_unit;
	map_size.y = sys->s_i.map_height * sys->s_i.pxl_unit;
	offset.x = (W_WIDTH - map_size.x) / 2;
	offset.y = (W_HEIGHT - map_size.y) / 2;
	draw_rect(sys, make_color(255, 0, 0, 0),
		make_int2(0, 0), make_int2(W_HEIGHT, W_WIDTH));
	render_map(sys, offset);
	render_pj(sys, offset);
}

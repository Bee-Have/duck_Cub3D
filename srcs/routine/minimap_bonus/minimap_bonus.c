/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 17:39:49 by amarini-          #+#    #+#             */
/*   Updated: 2022/06/15 17:20:59 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	draw_square_in_range(t_system *sys, t_color color, t_int2 pos
			, t_int2 ref_point)
{
	t_int2		current_pos;
	t_int2		raw_dist;
	long long	dist;

	current_pos.y = pos.y;
	raw_dist = make_int2(ref_point.y - pos.y, ref_point.x - pos.x);
	dist = (raw_dist.x * raw_dist.x + raw_dist.y * raw_dist.y);
	if (dist >= TILE_SIZE * 320)
		return ;
	while (current_pos.y < pos.y + TILE_SIZE)
	{
		current_pos.x = pos.x;
		while (current_pos.x < pos.x + TILE_SIZE)
		{
			raw_dist = make_int2(ref_point.y - current_pos.y,
					ref_point.x - current_pos.x);
			dist = (raw_dist.x * raw_dist.x + raw_dist.y * raw_dist.y);
			if (dist < TILE_SIZE * 120)
				draw_pxl(sys, current_pos, color);
			++current_pos.x;
		}
		++current_pos.y;
	}
}

static void	render_minimap(t_system *sys, t_int2 pos, t_int2 pj_pos)
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
				draw_square_in_range(sys, color, pos, pj_pos);
			pos.x += TILE_SIZE;
			++imap.x;
		}
		pos.y += TILE_SIZE;
		++imap.y;
	}
}

void	minimap_routine(t_system *sys, int corner)
{
	t_int2	area_start;
	t_int2	map_start;
	t_int2	pj_pos;
	int		half_size;

	half_size = TILE_SIZE / 4;
	pj_pos = make_int2(64, 64);
	if (corner == T_RIGHT)
		pj_pos = make_int2(64, W_WIDTH - 64);
	else if (corner == B_LEFT)
		pj_pos = make_int2(W_HEIGHT - 64, 64);
	else if (corner == B_RIGHT)
		pj_pos = make_int2(W_HEIGHT - 64, W_WIDTH - 64);
	area_start = make_int2(-sys->pj.pos.y * TILE_SIZE + pj_pos.y + half_size,
			-sys->pj.pos.x * TILE_SIZE + pj_pos.x + half_size);
	map_start = make_int2(area_start.y, area_start.x);
	render_minimap(sys, map_start,
		make_int2(pj_pos.y + half_size, pj_pos.x + half_size));
	render_pj_minimap(sys, pj_pos);
}

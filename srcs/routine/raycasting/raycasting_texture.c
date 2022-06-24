/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:40:06 by user42            #+#    #+#             */
/*   Updated: 2022/06/24 17:21:07 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	wall_texture_assignation(t_system *sys, t_raycast cast_info)
{
	if (cast_info.side == 1 && (int)sys->pj.pos.y < cast_info.hit.y)
		return (sys->s_i.north_texture);
	else if (cast_info.side == 1 && (int)sys->pj.pos.y > cast_info.hit.y)
		return (sys->s_i.south_texture);
	else if (cast_info.side == 0 && (int)sys->pj.pos.x < cast_info.hit.x)
		return (sys->s_i.east_texture);
	return (sys->s_i.west_texture);
}

static void	texture_collumn(t_system *sys, t_raycast cast_info, t_img text,
			t_int2 text_pos)
{
	double	step;
	double	tex_hit;
	int		y;
	t_color	color;

	draw_line(sys, make_int2(0, cast_info.x),
		make_int2(cast_info.wall_limits.y, cast_info.x), sys->s_i.ceiling);
	draw_line(sys, make_int2(cast_info.wall_limits.x, cast_info.x),
		make_int2(W_HEIGHT - 1, cast_info.x), sys->s_i.floor);
	step = 1.0 * text.size.y / cast_info.wall_height;
	tex_hit = (cast_info.wall_limits.y - W_HEIGHT
			/ 2 + cast_info.wall_height / 2) * step;
	y = cast_info.wall_limits.y;
	while (y < cast_info.wall_limits.x)
	{
		text_pos.y = (int)tex_hit & (text.size.y - 1);
		tex_hit += step;
		color.code = ((int *)text.addr)[text.size.y * text_pos.y + text_pos.x];
		draw_pxl(sys, make_int2(y, cast_info.x), color);
		y++;
	}
}

//here, wall_limits.x/y are both y positions, y = higest part | x = lowest part
void	texture_calculations(t_system *sys, t_raycast cast_info,
				double wall_dist)
{
	t_img	texture;
	double	wall_hit;
	t_int2	text_pos;

	if (cast_info.hit.y < 0 || cast_info.hit.x < 0
		|| cast_info.hit.y >= sys->s_i.map_height
		|| cast_info.hit.x >= sys->s_i.map_width)
	{
		cast_info.wall_limits = make_int2(W_HEIGHT / 2, W_HEIGHT / 2);
		texture_collumn(sys, cast_info, texture, text_pos);
	}
	texture = wall_texture_assignation(sys, cast_info);
	if (cast_info.side == 0)
		wall_hit = sys->pj.pos.y + wall_dist * cast_info.ray_dir.y;
	else
		wall_hit = sys->pj.pos.x + wall_dist * cast_info.ray_dir.x;
	wall_hit -= floor(wall_hit);
	text_pos.x = (int)(wall_hit * (double)texture.size.x);
	if (cast_info.side == 0 && cast_info.ray_dir.x > 0)
		text_pos.x = texture.size.x - text_pos.x - 1;
	if (cast_info.side == 1 && cast_info.ray_dir.y < 0)
		text_pos.x = texture.size.x - text_pos.x - 1;
	texture_collumn(sys, cast_info, texture, text_pos);
}

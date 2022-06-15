/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   racasting_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:40:06 by user42            #+#    #+#             */
/*   Updated: 2022/06/15 19:00:29 by user42           ###   ########.fr       */
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

//here, wall_limits.x/y are both y positions, y = higest part | x = lowest part
void	texture_calculations(t_system *sys, t_raycast cast_info,
							t_int2 wall_limits, double perp_wall_dist)
{
	t_img	texture;
	double	wall_hit;
	t_int2	text_pos;
	
	if (cast_info.hit.y < 0 || cast_info.hit.x < 0
		|| cast_info.hit.y >= ft_tab_len((void **)sys->s_i.map)
		|| cast_info.hit.x >= (int)ft_strlen(sys->s_i.map[cast_info.hit.y]))
		wall_limits = make_int2(W_HEIGHT / 2, W_HEIGHT / 2);
	texture = wall_texture_assignation(sys, cast_info);
	if (cast_info.side == 0)
		wall_hit = sys->pj.pos.y + perp_wall_dist * cast_info.ray_dir.y;
	else
		wall_hit = sys->pj.pos.x + perp_wall_dist * cast_info.ray_dir.x;
	wall_hit -= floor(wall_hit);
	
	text_pos.x = (int)(wall_hit * (double)texture.size.x);
	if (cast_info.side == 0 && cast_info.ray_dir.x > 0)
		text_pos.x = texture.size.x - text_pos.x - 1;
	if (cast_info.side == 1 && cast_info.ray_dir.y < 0)
		text_pos.x = texture.size.x - text_pos.x - 1;
	
	draw_line(sys, make_int2(0, cast_info.x),
		make_int2(wall_limits.y, cast_info.x), sys->s_i.ceiling);
	draw_line(sys, make_int2(wall_limits.x, cast_info.x),
		make_int2(W_HEIGHT - 1, cast_info.x), sys->s_i.floor);
	
	double	step;
	double	text_hit;
	int		y;
	step = 1.0 * texture.size.y / cast_info.wall_height;
	text_hit = (wall_limits.y - W_HEIGHT / 2 + cast_info.wall_height / 2) * step;
	y = wall_limits.y;
	while (y < wall_limits.x)
	{
		t_int2	start;
		t_color	color;
		int		*tmp;
		text_pos.y = (int)text_hit & (texture.size.y - 1);
		text_hit += step;
		start = make_int2(y, cast_info.x);
		tmp = (int *)texture.addr;
		color.code = tmp[texture.size.y * text_pos.y + text_pos.x];
		draw_pxl(sys, start, color);
		y++;
	}
}

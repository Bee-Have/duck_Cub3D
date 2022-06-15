/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:30:53 by amarini-          #+#    #+#             */
/*   Updated: 2022/06/15 18:28:33 by user42           ###   ########.fr       */
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
	
	int	text_x;
	text_x = (int)(wall_hit * (double)texture.size.x);
	if (cast_info.side == 0 && cast_info.ray_dir.x > 0)
		text_x = texture.size.x - text_x - 1;
	if (cast_info.side == 1 && cast_info.ray_dir.y < 0)
		text_x = texture.size.x - text_x - 1;
	
	draw_line(sys, make_int2(0, cast_info.x),
		make_int2(wall_limits.y, cast_info.x), sys->s_i.ceiling);
	draw_line(sys, make_int2(wall_limits.x, cast_info.x),
		make_int2(W_HEIGHT - 1, cast_info.x), sys->s_i.floor);
	
	double	step;
	double	text_pos;
	int		y;
	step = 1.0 * texture.size.y / cast_info.wall_height;
	text_pos = (wall_limits.y - W_HEIGHT / 2 + cast_info.wall_height / 2) * step;
	y = wall_limits.y;
	while (y < wall_limits.x)
	{
		t_int2	start;
		t_color	color;
		int		*tmp;
		int		text_y;
		text_y = (int)text_pos & (texture.size.y - 1);
		text_pos += step;
		start = make_int2(y, cast_info.x);
		tmp = (int *)texture.addr;
		color.code = tmp[texture.size.y * text_y + text_x];
		draw_pxl(sys, start, color);
		y++;
	}
}

int	render_rays(t_system *sys, t_raycast cast_info)
{
	double	perp_wall_dist;
	t_int2	bounds;
	int		wall_start;
	int		wall_end;

	if (cast_info.side == 0)
		perp_wall_dist = cast_info.side_dist.x - cast_info.delta_dist.x;
	else
		perp_wall_dist = cast_info.side_dist.y - cast_info.delta_dist.y;
	if ((int)perp_wall_dist == 0)
		cast_info.wall_height = W_HEIGHT;
	else
		cast_info.wall_height = (int)(W_HEIGHT / perp_wall_dist);
	wall_start = -cast_info.wall_height / 2 + W_HEIGHT / 2;
	if (wall_start < 0)
		wall_start = 0;
	wall_end = cast_info.wall_height / 2 + W_HEIGHT / 2;
	if (wall_end >= W_HEIGHT)
		wall_end = W_HEIGHT - 1;
	bounds = make_int2(wall_start, wall_end);
	texture_calculations(sys, cast_info, bounds, perp_wall_dist);
	return (1);
}

void	casting_rays(t_system *sys, t_raycast cast_info)
{
	int	hit_bool;

	cast_info.hit = make_int2((int)sys->pj.pos.y, (int)sys->pj.pos.x);
	hit_bool = 0;
	while (hit_bool == 0)
	{
		if (cast_info.side_dist.x < cast_info.side_dist.y)
		{
			cast_info.side_dist.x += cast_info.delta_dist.x;
			cast_info.hit.x += cast_info.step.x;
			cast_info.side = 0;
		}
		else
		{
			cast_info.side_dist.y += cast_info.delta_dist.y;
			cast_info.hit.y += cast_info.step.y;
			cast_info.side = 1;
		}
		if (cast_info.hit.y < 0 || cast_info.hit.x < 0
			|| cast_info.hit.y >= ft_tab_len((void **)sys->s_i.map)
			|| cast_info.hit.x >= (int)ft_strlen(sys->s_i.map[cast_info.hit.y])
			|| sys->s_i.map[cast_info.hit.y][cast_info.hit.x] == '1')
			hit_bool = render_rays(sys, cast_info);
	}
}

void	init_casting_info(t_system *sys, t_raycast *cast_info)
{
	if (cast_info->ray_dir.x == 0)
		cast_info->delta_dist.x = 1e30;
	else
		cast_info->delta_dist.x = fabs(1 / cast_info->ray_dir.x);
	if (cast_info->ray_dir.y == 0)
		cast_info->delta_dist.y = 1e30;
	else
		cast_info->delta_dist.y = fabs(1 / cast_info->ray_dir.y);
	cast_info->step = make_int2(1, 1);
	cast_info->side_dist = make_vec2((sys->pj.pos.y - (int)sys->pj.pos.y)
			* cast_info->delta_dist.y, (sys->pj.pos.x
				- (int)sys->pj.pos.x) * cast_info->delta_dist.x);
	if (cast_info->ray_dir.x < 0)
		cast_info->step.x = -1;
	else
		cast_info->side_dist.x = ((int)sys->pj.pos.x + 1.0 - sys->pj.pos.x)
			* cast_info->delta_dist.x;
	if (cast_info->ray_dir.y < 0)
		cast_info->step.y = -1;
	else
		cast_info->side_dist.y = ((int)sys->pj.pos.y + 1.0 - sys->pj.pos.y)
			* cast_info->delta_dist.y;
}

void	raycasting_routine(t_system *sys)
{
	t_raycast	cast_info;
	double		camera_x;

	cast_info.x = 0;
	while (cast_info.x < W_WIDTH)
	{
		camera_x = 2 * cast_info.x / (double)W_WIDTH - 1;
		cast_info.ray_dir = make_vec2(sys->pj.dir.y + sys->pj.plane.y * camera_x,
			sys->pj.dir.x + sys->pj.plane.x * camera_x);
		init_casting_info(sys, &cast_info);
		casting_rays(sys, cast_info);
		++cast_info.x;
	}
}

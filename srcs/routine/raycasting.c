/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:30:53 by amarini-          #+#    #+#             */
/*   Updated: 2022/05/28 20:48:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	raycasting_routine(t_system *sys)
{
	t_raycasting	cast_info;
	double	camera_x;
	t_vec2	ray_dir;
	t_int2	map;
	int		hit;

	cast_info.x = 0;
	while (cast_info.x < sys->s_i.screen.x)
	{
		map.x = (int)sys->pj.pos.x;
		map.y = (int)sys->pj.pos.y;
		hit = 0;
		camera_x = 2 * cast_info.x / (double)sys->s_i.screen.x - 1;
		ray_dir.x = (sys->pj.dir.x - sys->pj.pos.x) + sys->pj.plane.x * camera_x;
		ray_dir.y = (sys->pj.dir.y - sys->pj.pos.y) + sys->pj.plane.y * camera_x;
		if (ray_dir.x == 0)
			cast_info.delta_dist.x = 1e30;
		else
			cast_info.delta_dist.x = fabs(1 / ray_dir.x);
		if (ray_dir.y == 0)
			cast_info.delta_dist.y = 1e30;
		else
			cast_info.delta_dist.y = fabs(1 / ray_dir.y);
		if (ray_dir.x < 0)
		{
			cast_info.step.x = -1;
			cast_info.side_dist.x = (sys->pj.pos.x - map.x) * cast_info.delta_dist.x;
		}
		else
		{
			cast_info.step.x = 1;
			cast_info.side_dist.x = (map.x + 1.0 - sys->pj.pos.x) * cast_info.delta_dist.x;
		}
		if (ray_dir.y < 0)
		{
			cast_info.step.y = -1;
			cast_info.side_dist.y = (sys->pj.pos.y - map.y) * cast_info.delta_dist.y;
		}
		else
		{
			cast_info.step.y = 1;
			cast_info.side_dist.y = (map.y + 1.0 - sys->pj.pos.y) * cast_info.delta_dist.y;
		}
		while (hit == 0)
		{
			if (cast_info.side_dist.x < cast_info.side_dist.y)
			{
				cast_info.side_dist.x += cast_info.delta_dist.x;
				map.x += cast_info.step.x;
				cast_info.side = 0;
			}
			else
			{
				cast_info.side_dist.y += cast_info.delta_dist.y;
				map.y += cast_info.step.y;
				cast_info.side = 1;
			}
			//! the map will not always be square/rectangular
			if (map.y < 0 || map.y > ft_tab_len((void **)sys->s_i.map)
				|| map.x < 0 || map.x > (int)ft_strlen(sys->s_i.map[0])
				|| sys->s_i.map[map.y][map.x] == '1')
			{
				hit = 1;
				double	perp_wall_dist;
				t_int2	start;
				t_int2	end;
				int		line_height;
				int		draw_start;
				int		draw_end;

				if (cast_info.side == 0)
					perp_wall_dist = cast_info.side_dist.x - cast_info.delta_dist.x;
				else
					perp_wall_dist = cast_info.side_dist.y - cast_info.delta_dist.y;
				line_height = (int)(sys->s_i.screen.y / perp_wall_dist);
				draw_start = -line_height / 2 + sys->s_i.screen.y / 2;
				if (draw_start < 0)
					draw_start = 0;
				draw_end = line_height / 2 + sys->s_i.screen.y / 2;
				if (draw_end >= sys->s_i.screen.y)
					draw_end = sys->s_i.screen.y - 1;
				start.x = cast_info.x;
				end.x = cast_info.x;
				start.y = 0;
				end.y = draw_start;
				draw_line(sys, start, end, sys->s_i.ceiling);
				start.y = draw_end;
				end.y = sys->s_i.screen.y;
				draw_line(sys, start, end, sys->s_i.floor);
				start.y = draw_start;
				end.y = draw_end;
				if (cast_info.side == 1)
					draw_line(sys, start, end, sys->s_i.wall_north);
				else
					draw_line(sys, start, end, sys->s_i.wall_south);
			}
		}
		++cast_info.x;
	}
}

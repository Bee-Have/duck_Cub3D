/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:30:53 by amarini-          #+#    #+#             */
/*   Updated: 2022/05/28 20:01:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	render_ray(t_system *sys, double perp_wall_dist, int x, int side)
{
	t_int2	start;
	t_int2	end;
	int		line_height;
	int		wall_start;
	int		wall_end;
	
	line_height = (int)(sys->s_i.screen.y / perp_wall_dist);
	wall_start = -line_height / 2 + sys->s_i.screen.y / 2;
	if (wall_start < 0)
		wall_start = 0;
	wall_end = line_height / 2 + sys->s_i.screen.y / 2;
	if (wall_end >= sys->s_i.screen.y)
		wall_end = sys->s_i.screen.y - 1;
	start.x = x;
	end.x = x;
	start.y = 0;
	end.y = wall_start;
	draw_line(sys, start, end, sys->s_i.ceiling);
	start.y = wall_end;
	end.y = sys->s_i.screen.y;
	draw_line(sys, start, end, sys->s_i.floor);
	start.y = wall_start;
	end.y = wall_end;
	if (side == 1)
		draw_line(sys, start, end, sys->s_i.wall_west);
	else
		draw_line(sys, start, end, sys->s_i.wall_south);
}

t_vec2	calc_ray_direction(int x, t_system *sys)
{
	t_vec2	ray_dir;
	double	camera_x;
	
	camera_x = 2 * x / (double)sys->s_i.screen.x - 1;
	ray_dir.x = (sys->pj.dir.x - sys->pj.pos.x) + sys->pj.plane.x * camera_x;
	ray_dir.y = (sys->pj.dir.y - sys->pj.pos.y) + sys->pj.plane.y * camera_x;
	return (ray_dir);
}

void	raycasting_routine(t_system *sys)
{
	int		x;
	t_vec2	ray_dir;
	t_int2	map;
	t_vec2	side_dist;
	t_vec2	delta_dist;
	t_int2	step;
	int		hit;
	int		side;

	x = 0;
	while (x < sys->s_i.screen.x)
	{
		map.x = (int)sys->pj.pos.x;
		map.y = (int)sys->pj.pos.y;
		hit = 0;
		ray_dir = calc_ray_direction(x, sys);
		if (ray_dir.x == 0)
			delta_dist.x = 1e30;
		else
			delta_dist.x = fabs(1 / ray_dir.x);
		if (ray_dir.y == 0)
			delta_dist.y = 1e30;
		else
			delta_dist.y = fabs(1 / ray_dir.y);
		if (ray_dir.x < 0)
		{
			step.x = -1;
			side_dist.x = (sys->pj.pos.x - map.x) * delta_dist.x;
		}
		else
		{
			step.x = 1;
			side_dist.x = (map.x + 1.0 - sys->pj.pos.x) * delta_dist.x;
		}
		if (ray_dir.y < 0)
		{
			step.y = -1;
			side_dist.y = (sys->pj.pos.y - map.y) * delta_dist.y;
		}
		else
		{
			step.y = 1;
			side_dist.y = (map.y + 1.0 - sys->pj.pos.y) * delta_dist.y;
		}
		while (hit == 0)
		{
			if (side_dist.x < side_dist.y)
			{
				side_dist.x += delta_dist.x;
				map.x += step.x;
				side = 0;
			}
			else
			{
				side_dist.y += delta_dist.y;
				map.y += step.y;
				side = 1;
			}
			//! the map will not always be square/rectangular
			if (map.y < 0 || map.y > ft_tab_len((void **)sys->s_i.map)
				|| map.x < 0 || map.x > (int)ft_strlen(sys->s_i.map[0])
				|| sys->s_i.map[map.y][map.x] == '1')
			{
				hit = 1;
				if (side == 0)
					render_ray(sys, side_dist.x - delta_dist.x, x, side);
				else
					render_ray(sys, side_dist.y - delta_dist.y, x, side);
			}
		}
		++x;
	}
}

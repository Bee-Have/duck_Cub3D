/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:30:53 by amarini-          #+#    #+#             */
/*   Updated: 2022/05/17 18:54:13 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	raycasting_routine(t_mlx *mlx)
{
	int		x;
	double	camera_x;
	t_pos	ray_dir;
	t_vec2	map;
	t_pos	side_dist;
	t_pos	delta_dist;
	// double	perp_wall_dist;
	t_vec2	step;
	int		hit;
	int		side;

	x = 0;
	map.x = (int)mlx->pj.pos.x;
	map.y = (int)mlx->pj.pos.y;
	while (x < mlx->map_info.screen.x)
	{
		hit = 0;
		camera_x = 2 * x / (double)mlx->map_info.screen.x - 1;
		ray_dir.x = mlx->pj.dir.x + mlx->pj.plane.x * camera_x;
		ray_dir.y = mlx->pj.dir.y + mlx->pj.plane.y * camera_x;

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
			side_dist.x = (mlx->pj.pos.x - map.x) * delta_dist.x;
		}
		else
		{
			step.x = 1;
			side_dist.x = (map.x + 1.0 - mlx->pj.pos.x) * delta_dist.x;
		}
		if (ray_dir.y < 0)
		{
			step.y = -1;
			side_dist.y = (mlx->pj.pos.y - map.y) * delta_dist.y;
		}
		else
		{
			step.y = 1;
			side_dist.y = (map.y + 1.0 - mlx->pj.pos.y) * delta_dist.y;
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
			if (map.y < 0 || map.y > ft_tab_len((void **)mlx->map_info.map)
				|| map.x < 0 || map.x > (int)ft_strlen(mlx->map_info.map[0])
				|| mlx->map_info.map[map.y][map.x] == '1')
				hit = 1;
		}
		++x;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:25:34 by amarini-          #+#    #+#             */
/*   Updated: 2022/05/25 17:12:11 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_vec2	get_pj_pos(char **map)
{
	t_vec2	pj;
	int		row;
	int		col;

	pj.x = -1;
	pj.y = -1;
	row = 0;
	while (map[row] != NULL)
	{
		col = 0;
		while (map[row][col] != '\0')
		{
			if (map[row][col] == 'N' || map[row][col] == 'S'
				|| map[row][col] == 'E' || map[row][col] == 'W')
			{
				pj.y = row;
				pj.x = col;
				return (pj);
			}
			++col;
		}
		++row;
	}
	return (pj);
}

t_pj	init_pj(char **map)
{
	t_pj	pj;

	pj.pos = get_pj_pos(map);
	pj.rot = 0;
	if (map[(int)pj.pos.y][(int)pj.pos.x] == 'N')
		pj.rot = 90;
	if (map[(int)pj.pos.y][(int)pj.pos.x] == 'S')
		pj.rot = 270;
	if (map[(int)pj.pos.y][(int)pj.pos.x] == 'E')
		pj.rot = 0;
	if (map[(int)pj.pos.y][(int)pj.pos.x] == 'W')
		pj.rot = 180;
	pj.dir.x = pj.pos.x - (SPEED * cosf(pj.rot * (M_PI / 180)));
	pj.dir.y = pj.pos.y - (SPEED * sinf(pj.rot * (M_PI / 180)));
	pj.plane.x = 0;
	pj.plane.y = 0.1;
	return (pj);
}

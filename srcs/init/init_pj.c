/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:25:34 by amarini-          #+#    #+#             */
/*   Updated: 2022/06/14 20:55:27 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_vec2	get_pj_pos(char **map)
{
	t_vec2	pj;
	int		row;
	int		col;

	pj = make_vec2(-1, -1);
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
	pj.pos = make_vec2(pj.pos.y + 0.5, pj.pos.x + 0.5);
	if (map[(int)pj.pos.y][(int)pj.pos.x] == 'N')
		pj.dir = make_vec2(SPEED * sin(3 * M_PI / 2),
				SPEED * cos(3 * M_PI / 2));
	else if (map[(int)pj.pos.y][(int)pj.pos.x] == 'S')
		pj.dir = make_vec2(SPEED * sin(M_PI / 2), SPEED * cos(M_PI / 2));
	else if (map[(int)pj.pos.y][(int)pj.pos.x] == 'E')
		pj.dir = make_vec2(SPEED * sin(0), SPEED * cos(0));
	else if (map[(int)pj.pos.y][(int)pj.pos.x] == 'W')
		pj.dir = make_vec2(SPEED * sin(M_PI), SPEED * cos(M_PI));
	if (map[(int)pj.pos.y][(int)pj.pos.x] == 'N')
		pj.plane = make_vec2(0, 0.1);
	else if (map[(int)pj.pos.y][(int)pj.pos.x] == 'S')
		pj.plane = make_vec2(0, -0.1);
	else if (map[(int)pj.pos.y][(int)pj.pos.x] == 'E')
		pj.plane = make_vec2(0.1, 0);
	else if (map[(int)pj.pos.y][(int)pj.pos.x] == 'W')
		pj.plane = make_vec2(-0.1, 0);
	return (pj);
}

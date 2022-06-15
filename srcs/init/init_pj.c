/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:25:34 by amarini-          #+#    #+#             */
/*   Updated: 2022/06/15 18:28:42 by user42           ###   ########.fr       */
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
		pj.dir = make_vec2(DIR * sin(3 * M_PI / 2), DIR * cos(3 * M_PI / 2));
	else if (map[(int)pj.pos.y][(int)pj.pos.x] == 'S')
		pj.dir = make_vec2(DIR * sin(M_PI / 2), DIR * cos(M_PI / 2));
	else if (map[(int)pj.pos.y][(int)pj.pos.x] == 'E')
		pj.dir = make_vec2(DIR * sin(0), DIR * cos(0));
	else if (map[(int)pj.pos.y][(int)pj.pos.x] == 'W')
		pj.dir = make_vec2(DIR * sin(M_PI), DIR * cos(M_PI));
	if (map[(int)pj.pos.y][(int)pj.pos.x] == 'N')
		pj.plane = make_vec2(0, 0.3);
	else if (map[(int)pj.pos.y][(int)pj.pos.x] == 'S')
		pj.plane = make_vec2(0, -0.3);
	else if (map[(int)pj.pos.y][(int)pj.pos.x] == 'E')
		pj.plane = make_vec2(0.3, 0);
	else if (map[(int)pj.pos.y][(int)pj.pos.x] == 'W')
		pj.plane = make_vec2(-0.3, 0);
	return (pj);
}

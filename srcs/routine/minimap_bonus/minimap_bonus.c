/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 17:39:49 by amarini-          #+#    #+#             */
/*   Updated: 2022/06/06 18:25:46 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// this might need to change for pxl_unit.x
static int	minimap_pxl_unit(char **map)
{
	t_int2	pxl_unit;

	pxl_unit.x = (W_WIDTH / 4) / ft_strlen(map[0]);
	pxl_unit.y = (W_HEIGHT / 4) / ft_tab_len((void **)map);
	if (pxl_unit.x < pxl_unit.y)
		return (pxl_unit.y);
	return (pxl_unit.x);
}

static void	render_minimap(t_system *sys, t_int2 pos, int pxl_unit)
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
				color = make_color(255, 0, 74, 247);
			else
				color = make_color(255, 255, 110, 110);
			draw_square(sys, color, pos, pxl_unit);
			pos.x += pxl_unit;
			++imap.x;
		}
		pos.y += pxl_unit;
		++imap.y;
	}
}

void	minimap_routine(t_system *sys, int corner)
{
	t_int2	area_start;
	t_int2	map_start;
	t_int2	offset;
	int		pxl_unit;

	pxl_unit = minimap_pxl_unit(sys->s_i.map);
	offset = make_int2((W_HEIGHT / 4 - ft_tab_len((void **)sys->s_i.map)
				* pxl_unit) / 2, (W_WIDTH / 4 - ft_strlen(sys->s_i.map[0])
				* pxl_unit) / 2);
	area_start = make_int2(0, 0);
	if (corner == T_RIGHT)
		area_start.x = W_WIDTH - W_WIDTH / 4;
	else if (corner == B_LEFT)
		area_start.y = W_HEIGHT - W_HEIGHT / 4;
	else if (corner == B_RIGHT)
		area_start = make_int2(W_HEIGHT - W_HEIGHT / 4, W_WIDTH - W_WIDTH / 4);
	map_start = make_int2(area_start.y + offset.y, area_start.x + offset.x);
	render_minimap(sys, map_start, pxl_unit);
	render_pj_minimap(sys, map_start, pxl_unit);
}
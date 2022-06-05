/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_pj_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 18:28:28 by amarini-          #+#    #+#             */
/*   Updated: 2022/06/05 14:51:11 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	render_pj_minimap(t_system *sys, t_int2 map_start, int pxl_unit)
{
	t_color	color;
	t_int2	dir;
	t_int2	pos;
	int		size;
	
	color = make_color(255, 255, 0, 0);
	size = pxl_unit / 2;
	pos.y = (map_start.y + (sys->pj.pos.y * pxl_unit)) - (pxl_unit - size) / 2;
	pos.x = (map_start.x + (sys->pj.pos.x * pxl_unit)) - (pxl_unit - size) / 2;
	draw_circle(sys, color, pos, size);
	pos = make_int2(pos.y + size / 2, pos.x + size / 2);
	dir.y = pos.y - (pxl_unit * sinf(sys->pj.rot * (M_PI / 180)));
	dir.x = pos.x - (pxl_unit * cosf(sys->pj.rot * (M_PI / 180)));
	color = make_color(255, 0, 255, 0);
	draw_line(sys, pos, dir, color);
}

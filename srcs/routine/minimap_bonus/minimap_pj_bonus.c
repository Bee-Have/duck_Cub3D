/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_pj_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 18:28:28 by amarini-          #+#    #+#             */
/*   Updated: 2022/06/24 15:22:05 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duckling3d_bonus.h"

void	render_pj_minimap(t_system *sys, t_int2 pj_pos)
{
	t_color	color;
	t_int2	dir;
	t_int2	middle;
	int		size;

	color = make_color(255, 255, 0, 0);
	size = TILE_SIZE / 2;
	draw_circle(sys, color, pj_pos, size);
	middle = make_int2(pj_pos.y + size / 2, pj_pos.x + size / 2);
	dir.y = sys->pj.dir.y * TILE_SIZE * 2 + middle.y;
	dir.x = sys->pj.dir.x * TILE_SIZE * 2 + middle.x;
	color = make_color(255, 0, 0, 0);
	draw_line(sys, middle, dir, color);
}

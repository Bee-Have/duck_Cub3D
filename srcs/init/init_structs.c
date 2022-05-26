/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:14:04 by amarini-          #+#    #+#             */
/*   Updated: 2022/05/26 15:32:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_color	make_color(unsigned char a, unsigned char r, unsigned char g, unsigned char b)
{
	t_color	color;

	color.a = a;
	color.r = r;
	color.g = g;
	color.b = b;
	color.code = (color.a << 24) + (color.r << 16) + (color.g << 8) + color.b;
	return (color);
}

t_screen_info	init_screen_info(char **map, int width, int height)
{
	t_screen_info	s_i;

	s_i.screen.x = width;
	s_i.screen.y = height;
	s_i.map = map;
	s_i.pxl_unit = 0;
	// this part will be partly automatised && some of them will be textures
	s_i.floor = make_color(255, 255, 255, 255);// white
	s_i.ceiling = make_color(255, 0, 0, 255);// blue
	s_i.wall_north = make_color(255, 255, 0, 0);// red
	s_i.wall_south = make_color(255, 0, 255, 0);// green
	s_i.wall_east = make_color(255, 0, 0, 0);// black
	s_i.wall_west = make_color(255, 255, 255, 0);// yellow
	return (s_i);
}

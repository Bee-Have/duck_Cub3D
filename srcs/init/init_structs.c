/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:14:04 by amarini-          #+#    #+#             */
/*   Updated: 2022/05/25 17:08:55 by amarini-         ###   ########.fr       */
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
	t_screen_info	screen_info;

	screen_info.screen.x = width;
	screen_info.screen.y = height;
	screen_info.map = map;
	screen_info.pxl_unit = 0;
	// this part will be partly automatised && some of them will be textures
	screen_info.floor = make_color(255, 255, 255, 255);// white
	screen_info.ceiling = make_color(255, 0, 0, 0);// black
	screen_info.wall_north = make_color(255, 255, 0, 0);// red
	screen_info.wall_south = make_color(255, 0, 0, 255);// blue
	screen_info.wall_east = make_color(255, 0, 255, 0);// green
	screen_info.wall_west = make_color(255, 255, 255, 0);// yellow
	return (screen_info);
}

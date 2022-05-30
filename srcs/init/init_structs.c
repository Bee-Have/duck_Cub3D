/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:14:04 by amarini-          #+#    #+#             */
/*   Updated: 2022/05/30 16:34:07 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_int2	make_int2(int y, int x)
{
	t_int2	vector;
	
	vector.y = y;
	vector.x = x;
	return (vector);
}

t_vec2	make_vec2(double y, double x)
{
	t_vec2	vector;
	
	vector.y = y;
	vector.x = x;
	return (vector);
}

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
	//to throw away
	s_i.wall_north = make_color(255, 255, 0, 0);// red
	s_i.wall_south = make_color(255, 0, 255, 0);// green
	s_i.wall_east = make_color(255, 0, 0, 0);// black
	s_i.wall_west = make_color(255, 255, 255, 0);// yellow
	return (s_i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:14:04 by amarini-          #+#    #+#             */
/*   Updated: 2022/06/06 15:50:26 by ldutriez         ###   ########.fr       */
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

t_color	make_color(unsigned char a,
				unsigned char r, unsigned char g, unsigned char b)
{
	t_color	color;

	color.a = a;
	color.r = r;
	color.g = g;
	color.b = b;
	color.code = (color.a << 24) + (color.r << 16) + (color.g << 8) + color.b;
	return (color);
}

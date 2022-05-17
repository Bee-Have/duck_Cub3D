/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:14:04 by amarini-          #+#    #+#             */
/*   Updated: 2022/05/17 18:26:40 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_map_info	init_map_info(char **map, int width, int height)
{
	t_map_info	map_info;

	map_info.map = map;
	map_info.pxl_unit = 0;
	map_info.screen.x = width;
	map_info.screen.y = height;
	return (map_info);
}

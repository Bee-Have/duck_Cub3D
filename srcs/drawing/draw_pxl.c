/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pxl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:19:28 by amarini-          #+#    #+#             */
/*   Updated: 2022/06/14 20:55:27 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_pxl(t_system *sys, t_int2 pos, t_color color)
{
	int	*tmp;

	if (pos.x < 0 || pos.x > W_WIDTH || pos.y < 0 || pos.y > W_HEIGHT)
		return ;
	tmp = (int *)sys->mlx.img.addr;
	tmp[(pos.y * W_WIDTH) + pos.x] = color.code;
}

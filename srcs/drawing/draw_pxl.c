/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pxl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:19:28 by amarini-          #+#    #+#             */
/*   Updated: 2022/05/16 16:19:44 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_pxl(t_mlx *mlx, t_vec2 pos, t_color color)
{
	int	*tmp;

	if (pos.x < 0 || pos.x > 1920 || pos.y < 0 || pos.y > 1080)
		return ;
	tmp = (int *)mlx->img.addr;
	tmp[(pos.y * 1920) + pos.x] = color.code;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_end.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 19:26:03 by user42            #+#    #+#             */
/*   Updated: 2022/06/04 02:02:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_textures(t_screen_info s_i)
{
	mlx_destroy_image(s_i.)
}

void	end_simulation(t_system *sys)
{
	mlx_destroy_window(sys->mlx.mlx, sys->mlx.win);
	mlx_destroy_display(sys->mlx.mlx);
}

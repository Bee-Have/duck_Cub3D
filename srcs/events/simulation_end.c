/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_end.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 19:26:03 by user42            #+#    #+#             */
/*   Updated: 2022/06/04 14:08:27 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//! I will implement this part when the textures will be properly used
// static void	free_textures(t_system *sys)
// {
// 	mlx_destroy_image(sys->mlx.mlx, sys->s_i.north_texture.img);
// 	mlx_destroy_image(sys->mlx.mlx, sys->s_i.south_texture.img);
// 	mlx_destroy_image(sys->mlx.mlx, sys->s_i.west_texture.img);
// 	mlx_destroy_image(sys->mlx.mlx, sys->s_i.east_texture.img);
// }

void	end_simulation(t_system *sys)
{
	ft_free_tab((void **)sys->s_i.map);
	sys->s_i.map = NULL;
	// free_textures(sys);
	mlx_destroy_image(sys->mlx.mlx, sys->mlx.img.img);
	mlx_destroy_window(sys->mlx.mlx, sys->mlx.win);
	mlx_destroy_display(sys->mlx.mlx);
	sys->mlx.mlx = NULL;
	exit(EXIT_SUCCESS);
}

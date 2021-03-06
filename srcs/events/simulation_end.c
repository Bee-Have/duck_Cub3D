/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_end.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 19:26:03 by user42            #+#    #+#             */
/*   Updated: 2022/06/24 18:44:44 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//! I will implement this part when the textures will be properly used
static void	free_textures(t_system *sys)
{
	if (sys->s_i.north_texture.img != NULL)
		mlx_destroy_image(sys->mlx.mlx, sys->s_i.north_texture.img);
	if (sys->s_i.south_texture.img != NULL)
		mlx_destroy_image(sys->mlx.mlx, sys->s_i.south_texture.img);
	if (sys->s_i.west_texture.img != NULL)
		mlx_destroy_image(sys->mlx.mlx, sys->s_i.west_texture.img);
	if (sys->s_i.east_texture.img != NULL)
		mlx_destroy_image(sys->mlx.mlx, sys->s_i.east_texture.img);
}

int	end_simulation(t_system *sys, int exit_code)
{
	if (sys->s_i.map != NULL)
		ft_free_tab((void **)sys->s_i.map);
	sys->s_i.map = NULL;
	free_textures(sys);
	mlx_destroy_image(sys->mlx.mlx, sys->mlx.img.img);
	mlx_destroy_window(sys->mlx.mlx, sys->mlx.win);
	mlx_destroy_display(sys->mlx.mlx);
	sys->mlx.mlx = NULL;
	exit(exit_code);
}

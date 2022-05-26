/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:10:57 by amarini-          #+#    #+#             */
/*   Updated: 2022/05/26 14:42:26 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int ac, char **av)
{
	t_mlx	*mlx;

	if (ac != 2)
	{
		ft_putstr_fd(2, "Error\nUsage: cub3D path_to_file.cub\n");
		return (EXIT_FAILURE);
	}
	mlx = init_mlx(1920, 1080);
	if (parse_map(mlx, av[1]) != 0)
		return (EXIT_FAILURE);
	// init map
	//! this is temporary because the file will not only include the map
	// mlx->map_info = init_map_info(ft_get_file(av[1]), 1920, 1080);
	// init pj

	// mlx->pj = init_pj(mlx->map_info.map);
	// // start mlx routine
	// mlx_routine(mlx);
	// ft_free_tab((void **)mlx->map_info.map);

	free(mlx);
	return (EXIT_SUCCESS);
}

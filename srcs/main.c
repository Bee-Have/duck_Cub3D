/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:10:57 by amarini-          #+#    #+#             */
/*   Updated: 2022/05/29 20:43:39 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int ac, char **av)
{
	t_system	*sys;

	// call parsing
	if (ac != 2)
	{
		ft_putstr_fd(2, "Error\nUsage: cub3D path_to_file.cub\n");
		return (EXIT_FAILURE);
	}
	//! sys does not need to be a pointer (no need for malloc)
	sys = (t_system *)malloc(sizeof(t_system));
	if (!sys)
		return (EXIT_FAILURE);
	// init mlx
	//! WARNING window size will be given from file
	sys->mlx = init_mlx(1920, 1080);
	if (parse_map(sys, av[1]) != 0)
		return (EXIT_FAILURE);
	// init map
	//! this is temporary because the file will not only include the map
	sys->s_i = init_screen_info(ft_get_file(av[1]), 1920, 1080);
	sys->events = init_events();
	// init pj
	sys->pj = init_pj(sys->s_i.map);
	// start mlx routine
	mlx_routine(sys);
	ft_free_tab((void **)sys->s_i.map);
	free(sys);
	return (EXIT_SUCCESS);
}

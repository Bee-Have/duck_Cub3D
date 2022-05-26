/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:10:57 by amarini-          #+#    #+#             */
/*   Updated: 2022/05/26 15:32:39 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int ac, char **av)
{
	t_system	*sys;

	// call parsing
	if (ac < 2 /*|| parsing function returns bad*/)
		return (EXIT_FAILURE);
	sys = (t_system *)malloc(sizeof(t_system));
	if (!sys)
		return (EXIT_FAILURE);
	// init mlx
	//! WARNING window size will be given from file
	sys->mlx = init_mlx(1920, 1080);
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

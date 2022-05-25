/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:10:57 by amarini-          #+#    #+#             */
/*   Updated: 2022/05/25 17:10:37 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int ac, char **av)
{
	t_system	*system;

	// call parsing
	if (ac < 2 /*|| parsing function returns bad*/)
		return (EXIT_FAILURE);
	system = (t_system *)malloc(sizeof(t_system));
	if (!system)
		return (EXIT_FAILURE);
	// init mlx
	//! WARNING window size will be given from file
	system->mlx = init_mlx(1920, 1080);
	// init map
	//! this is temporary because the file will not only include the map
	system->screen_info = init_screen_info(ft_get_file(av[1]), 1920, 1080);
	system->events = init_events();
	// init pj
	system->pj = init_pj(system->screen_info.map);
	// start mlx routine
	// mlx_routine(system);
	ft_free_tab((void **)system->screen_info.map);
	free(system);
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:10:57 by amarini-          #+#    #+#             */
/*   Updated: 2022/05/30 17:12:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int ac, char **av)
{
	t_system	sys;

	if (ac != 2)
	{
		ft_putstr_fd(2, "Error\nUsage: cub3D path_to_file.cub\n");
		return (EXIT_FAILURE);
	}
	// init mlx
	sys.mlx = init_mlx();
	if (parse_map(&sys, av[1]) != 0)
		return (EXIT_FAILURE);
	sys.events = init_events();
	sys.pj = init_pj(sys.s_i.map);
	// start mlx routine
	mlx_routine(sys);
	ft_free_tab((void **)sys.s_i.map);
	return (EXIT_SUCCESS);
}

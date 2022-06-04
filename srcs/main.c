/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:10:57 by amarini-          #+#    #+#             */
/*   Updated: 2022/06/04 15:14:30 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int ac, char **av)
{
	t_system	sys;

	ft_bzero(&sys, sizeof(t_system));
	if (ac != 2)
	{
		ft_putstr_fd(2, "Error\nUsage: cub3D path_to_file.cub\n");
		return (EXIT_FAILURE);
	}
	// init mlx
	sys.mlx = init_mlx();
	if (parse_map(&sys, av[1]) != 0)
		end_simulation(&sys, EXIT_FAILURE);
	sys.events = init_events();
	sys.pj = init_pj(sys.s_i.map);
	// start mlx routine
	mlx_routine(sys);
	end_simulation(&sys, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

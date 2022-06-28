/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:10:57 by amarini-          #+#    #+#             */
/*   Updated: 2022/06/28 04:53:40 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duckling3d_bonus.h"

int	main(int ac, char **av)
{
	t_system	sys;
	char		window_name[11];

	ft_bzero(&sys, sizeof(t_system));
	if (ac != 2)
	{
		ft_putstr_fd(2, "Error\nUsage: cub3D path_to_file.cub\n");
		return (EXIT_FAILURE);
	}
	ft_strcpy("duckling3D", window_name);
	sys.mlx = init_mlx(window_name);
	if (parse_map(&sys, av[1]) != 0)
		end_simulation(&sys, EXIT_FAILURE);
	sys.pj = init_pj(sys.s_i.map);
	sys.s_i.map[(int)sys.pj.pos.y][(int)sys.pj.pos.x] = '0';
	mlx_routine(sys);
	end_simulation(&sys, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

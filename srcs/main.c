/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:10:57 by amarini-          #+#    #+#             */
/*   Updated: 2022/05/16 20:08:35 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int ac, char *av)
{
	t_mlx	*mlx;

	//call parsing
	if (ac != 2 /*|| parsing function returns bad*/)
		return (EXIT_FAILURE);
	//init mlx
	//!WARNING window size will be given from file
	mlx = init_mlx(1920, 1080);
	//init map
	//!this is temporary because the file will not only include the map
	mlx->map = ft_get_file(av[1]);
	//init pj
	return (EXIT_SUCCESS);
}

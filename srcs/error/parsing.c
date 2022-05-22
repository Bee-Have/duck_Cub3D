/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:12:32 by amarini-          #+#    #+#             */
/*   Updated: 2022/05/22 21:36:25 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
*	Check if path is valid and the file is readable.
*  Return 0 on success, 1 on error.
*/
static int	check_path_validity(char *path_to_file)
{
	int	path_length;

	path_length = ft_strlen(path_to_file);
	if (path_length < 5)
	{
		ft_putstr("Error\nFile path is too short.\n");
		return (1);
	}
	if (ft_strcmp(path_to_file + path_length - 4, ".cub") == b_false)
	{
		ft_putstr("Error\nFile extension is not \".cub\".\n");
		return (1);
	}
	if (ft_is_valid_file_path(path_to_file) == b_false)
	{
		ft_putstr("Error\nUnable to open the file.\n");
		return (1);
	}
	return (0);
}

//parsing of all args in file

/*
*	This function will run tests on the path and then on the file.
* If everything is correct the map data will be saved in the mlx struct.
* Return 0 on success, 1 on error.
*/
int	parse_map(t_mlx *mlx, char *path_to_file)
{
	(void)mlx;
	if (check_path_validity(path_to_file) != 0)
		return (1);
	else
		ft_putstr("path is valid\n");
	return (0);
}

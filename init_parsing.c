/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 13:12:51 by user42            #+#    #+#             */
/*   Updated: 2021/04/23 13:43:03 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_infos(char *path)
{
	int		index;
	int		read;
	void	*mlx;
	t_list	*list;

	if (!path)
		return ;
	index = 0;
	mlx = mlx_init();
	list = init_struct();
	read = ft_get_file(path, &list->file);
	if (read == -1)
		simple_error("could not read map file");
	while (list->file[index] != NULL)
	{
		if (list->found_map == 0)
			treat_infos(list->file[index], &list);
		if (list->found_map == 1)
			break ;
		index++;
	}
	list->map = map_register(list->file, &index);
	print_map(list->map);
	free_list(&list);
	return ;
}

void	treat_infos(char *line, t_list **list)
{
	if (line[0] == '\0')
		return ;
	else if (line[0] == 'R')
	{
		(*list)->res = res_colors_register(line, 2);
		if ((*list)->res[2] != NULL)
			simple_error("incorect number of agruments for Resolution");
	}
	else if (line[0] == 'N' && line[1] == 'O')
		(*list)->no = texture_register(line);
	else if (line[0] == 'S' && line[1] == 'O')
		(*list)->so = texture_register(line);
	else if (line[0] == 'W' && line[1] == 'E')
		(*list)->we = texture_register(line);
	else if (line[0] == 'E' && line[1] == 'A')
		(*list)->ea = texture_register(line);
	else if (line[0] == 'S')
		(*list)->sprite = texture_register(line);
	else if (line[0] == 'F')
	{
		(*list)->floor = res_colors_register(line, 3);
		if ((*list)->floor[3] != NULL)
			simple_error("incorect number of arguments for Floor Color");
	}
	else if (line[0] == 'C')
	{
		(*list)->ceiling = res_colors_register(line, 3);
		if ((*list)->ceiling[3] != NULL)
			simple_error("incorect number of arguments for Ceiling Color");
	}
	else if (str_cmp(0, line, "01") == 1)
		(*list)->found_map = 1;
	return ;
}

void	print_map(char **map)
{
	int		row;
	
	row = 0;
	while (map[row] != NULL)
	{
		printf("[%s]\n", map[row]);
		row++;
	}
	return ;
}

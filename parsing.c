/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 13:12:51 by user42            #+#    #+#             */
/*   Updated: 2021/04/21 17:12:43 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_infos(char *path)
{
	char	**file;
	int		index;
	int		read;
	t_list	*list;

	if (!path)
		return ;
	printf("got file path\n");
	index = 0;
	list = init_struct();
	read = ft_get_file(path, &file);
	if (read == -1)
		simple_error();
	printf("got file infos\n");
	while (file[index] != NULL)
	{
		printf("gonna treat this line\n");
		printf("[%s]\n", file[index]);
		if (list->found_map == 0)
			treat_infos(file[index], &list);
		if (list->found_map == 1)
			break ;
		index++;
	}
	list->map = map_register(file, &index);
	free_list(&list);
	return ;
}

void	treat_infos(char *line, t_list **list)
{
	if (line[0] == '\0')
	{
		printf("ingnoring empty line\n");
		return ;
	}
	else if (line[0] == 'R')
	{
		printf("found resolution\n");
		(*list)->res = calc_resolution(line, 2);
		print_map((*list)->res);
		if ((*list)->res[2] != NULL)
			simple_error();
	}
	else if (line[0] == 'N' && line[1] == 'O')
	{
		printf("found north texture\n");
	}
	else if (line[0] == 'S' && line[1] == 'O')
	{
		printf("found south texture\n");
	}
	else if (line[0] == 'W' && line[1] == 'E')
	{
		printf("found west texture\n");
	}
	else if (line[0] == 'E' && line[1] == 'A')
	{
		printf("found east texture\n");
	}
	else if (line[0] == 'S')
	{
		printf("found sprite texture\n");
	}
	else if (line[0] == 'F')
	{
		printf("found floor color\n");
		(*list)->floor = calc_resolution(line, 3);
		if ((*list)->floor[3] != NULL)
			simple_error();
	}
	else if (line[0] == 'C')
	{
		printf("found floor color\n");
		(*list)->ceiling = calc_resolution(line, 3);
		if ((*list)->ceiling[3] != NULL)
			simple_error();
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

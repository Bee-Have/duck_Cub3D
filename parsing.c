/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 13:12:51 by user42            #+#    #+#             */
/*   Updated: 2021/04/20 16:25:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_infos(char *path)
{
	int		fdmap;
	char	*line;
	int		read;
	t_list	*list;

	if (!path)
		return ;
	printf("got infos\n");
	read = 1;
	fdmap = 0;
	fdmap = open(path, O_RDONLY);
	list = init_struct();
	if (fdmap >= 1)
	{
		while (read > 0 && read != -1)
		{
			read = get_next_line(fdmap, &line);
			printf("gonna treat new line\n");
			treat_infos(line, &list);
			free(line);
		}
		free(line);
	}
	return ;
}

void	treat_infos(char *line, t_list **list)
{
	//printf("in function to treat infos\n");
	if (line[0] == '\0')
	{
		printf("ingnoring empty line\n");
		return ;
	}
	if (line[0] == 'R')
	{
		printf("found resolution\n");
		(*list)->res = calc_resolution(line, 2);
	}
	if (line[0] == 'N' && line[1] == 'O')
	{
		printf("found north texture\n");
	}
	if (line[0] == 'S' && line[1] == 'O')
	{
		printf("found south texture\n");
	}
	if (line[0] == 'W' && line[1] == 'E')
	{
		printf("found west texture\n");
	}
	if (line[0] == 'E' && line[1] == 'A')
	{
		printf("found east texture\n");
	}
	if (line[0] == 'S')
	{
		printf("found sprite texture\n");
	}
	if (line[0] == 'F')
	{
		printf("found floor color\n");
		(*list)->floor = calc_resolution(line, 3);
	}
	if (line[0] == 'C')
	{
		printf("found floor color\n");
		(*list)->ceiling = calc_resolution(line, 3);
	}
	return ;
}

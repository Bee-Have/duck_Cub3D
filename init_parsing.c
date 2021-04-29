/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 13:12:51 by user42            #+#    #+#             */
/*   Updated: 2021/04/29 17:18:00 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3D.h"

void	get_infos(char *path)
{
	int		index;
	int		read;
	t_cub	*list;

	if (!path)
		return ;
	index = 0;
	list = init_struct();
	read = ft_get_file(path, &list->file);
	//can send t_cub
	if (read == -1)
		simple_error(&list, "could not read '.cub' file");
	while (list->file[index] != NULL)
	{
		if (list->found_map == 0)
			treat_infos(list->file[index], &list);
		if (list->found_map == 1)
			break ;
		index++;
	}
	map_register(&list, &index);
	print_map(list->map);
	init_minilibx(&list);
	free_list(&list);
	return ;
}

void	treat_infos(char *line, t_cub **list)
{
	void	(*pars[2])(t_cub **, char *) = {res_RGB_register, texture_register};

	if (line[0] == '\0')
		return ;
	else if (line[0] == 'R')
		pars[0](list, line);
	else if ((line[0] == 'N' && line[1] == 'O')
			|| (line[0] == 'S' && line[1] == 'O')
			|| (line[0] == 'W' && line[1] == 'E')
			|| (line[0] == 'E' && line[1] == 'A')
			|| line[0] == 'S')
		pars[1](list, line);
	else if (line[0] == 'F' || line[0] == 'C')
		pars[0](list, line);
	else if (str_cmp(0, line, "01") == 1)
		(*list)->found_map = 1;
	return ;
}

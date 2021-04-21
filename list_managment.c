/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_managment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 13:42:11 by user42            #+#    #+#             */
/*   Updated: 2021/04/21 17:08:12 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_list	*init_struct(void)
{
	t_list	*list;
	
	list = NULL;
	list = (t_list *)malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	// list->res = (int *)malloc(2 * sizeof(char));
	// if (!list->res)
	// 	return (NULL);
	// list->floor = (int *)malloc(3 * sizeof(char));
	// if (!list->floor)
	// 	return (NULL);
	// list->ceiling = (int *)malloc(3 * sizeof(char));
	// if (!list->ceiling)
	// 	return (NULL);
	list->found_map = 0;
	return (list);
}

void	free_list(t_list **list)
{
	int		index;

	index = 0;
	if ((*list)->res)
		free((*list)->res);
	if ((*list)->floor)
		free((*list)->floor);
	if ((*list)->ceiling)
		free((*list)->ceiling);
	if ((*list)->map)
	{
		while ((*list)->map[index] != NULL)
		{
			free((*list)->map[index]);
			index++;
		}
		free((*list)->map);
	}
	free(list);
}
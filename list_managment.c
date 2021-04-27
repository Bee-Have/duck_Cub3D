/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_managment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 13:42:11 by user42            #+#    #+#             */
/*   Updated: 2021/04/27 10:56:33 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3D.h"

t_list	*init_struct(void)
{
	t_list	*list;
	
	list = NULL;
	list = (t_list *)malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->found_map = 0;
	return (list);
}

void	free_list(t_list **list)
{
	free_2d_array(&(*list)->file);
	if ((*list)->res)
		free_2d_array(&(*list)->res);
	if ((*list)->floor)
		free_2d_array(&(*list)->floor);
	if ((*list)->ceiling)
		free_2d_array(&(*list)->ceiling);
	if ((*list)->map)
		free_2d_array(&(*list)->map);
	free((*list)->no);
	free((*list)->so);
	free((*list)->ea);
	free((*list)->we);
	free((*list)->sprite);
	free((*list));
}

void	free_2d_array(char ***array)
{
	int		index;

	index = 0;
	while ((*array)[index] != NULL)
	{
		free((*array)[index]);
		index++;
	}
	free((*array));
	return ;
}
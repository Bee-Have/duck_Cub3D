/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_managment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 13:42:11 by user42            #+#    #+#             */
/*   Updated: 2021/04/20 14:37:32 by user42           ###   ########.fr       */
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
	//list->res = (int *)malloc(2 * sizeof(char));
	//if (!list->res)
	//	return (NULL);
	list->floor = (int *)malloc(3 * sizeof(char));
	if (!list->floor)
		return (NULL);
	list->ceiling = (int *)malloc(3 * sizeof(char));
	if (!list->ceiling)
		return (NULL);
	return (list);
}
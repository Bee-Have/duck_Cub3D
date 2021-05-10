/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 12:02:14 by amarini-          #+#    #+#             */
/*   Updated: 2021/05/10 13:55:59 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3D.h"

void	map_register(t_cub **cub, int *index)
{
	int		length;
	char	**result;

	length = (*index);
	while ((*cub)->file[length] != NULL
			&& str_cmp(0, (*cub)->file[length], "012NSEW") == 1)
		length++;
	length = length - (*index);
	result = (char **)malloc((length + 1) * sizeof(char *));
	if (!result)
		return ;
	result[length--] = NULL;
	while (length >= 0)
	{
		result[length] = ft_strcpy((*cub)->file[(*index) + length]);
		length--;
	}
	while ((*cub)->file[(*index)] != NULL
			&& str_cmp(0, (*cub)->file[(*index)], "012NSEW") == 1)
		(*index)++;
	(*cub)->map = (result);
	map_open_check(cub);
	map_pj_check(cub);
	(*cub)->longest_map = max_line_len((*cub)->map);
}

void	map_open_check(t_cub **cub)
{
	int		index;
	int		i;

	index = 0;
	i = 0;
	while ((*cub)->map[index] != NULL)
	{
		while ((*cub)->map[index][i] != '\0')
		{
			if (str_cmp((*cub)->map[index][i], NULL, "02NSEW") == 1
				&& open_test((*cub)->map, i, index) == 0)
				simple_error(cub, "Your map is not closed or there is a wrong character inside");
			i++;
		}
		i = 0;
		index++;
	}
	return ;
}

int		open_test(char **map, int i, int index)
{
	int		icpy;
	int		ndxcpy;

	icpy = i - 1;
	ndxcpy = index - 1;
	if (str_cmp(map[index][icpy], NULL, "012NSEW") == 0)
		return (0);
	icpy = i + 1;
	if (str_cmp(map[index][icpy], NULL, "012NSEW") == 0)
		return (0);
	if (str_cmp(map[ndxcpy][i], NULL, "012NSEW") == 0)
		return (0);
	ndxcpy = index + 1;
	if (str_cmp(map[ndxcpy][i], NULL, "012NSEW") == 0)
		return (0);
	return (1);
}

void	map_pj_check(t_cub **cub)
{
	int		pj;
	int		index;
	int		i;

	pj = 0;
	index = 0;
	i = 0;
	while ((*cub)->map[index] != NULL)
	{
		while ((*cub)->map[index][i] != '\0')
		{
			if (str_cmp((*cub)->map[index][i], NULL, "NSEW") == 1)
				pj++;
			if (pj > 1)
				simple_error(cub, "There is more then one player on the map");
			i++;
		}
		i = 0;
		index++;
	}
	if (pj == 0)
		simple_error(cub, "There is no player on the map");
	return ;
}

int		max_line_len(char **map)
{
	int		collumn;
	int		row;
	int		result;

	collumn = 0;
	row = 0;
	result = 0;
	while (map[row] != NULL)
	{
		while (map[row][collumn] != '\0')
			collumn++;
		if (result < collumn)
			result = collumn;
		collumn = 0;
		row++;
	}
	return (result);
}

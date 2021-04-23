/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 12:02:14 by amarini-          #+#    #+#             */
/*   Updated: 2021/04/23 10:41:44 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	**map_register(char **file, int *index)
{
	int		i;
	int		length;
	char	**result;

	length = (*index);
	while (file[length] != NULL && str_cmp(0, file[length], "012NSEW") == 1)
		length++;
	length = length - (*index);
	result = (char **)malloc((length + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	result[length--] = NULL;
	while (length >= 0)
	{
		result[length] = ft_strcpy(file[(*index) + length]);
		length--;
	}
	while (file[(*index)] != NULL && str_cmp(0, file[(*index)], "012NSEW") == 1)
		(*index)++;
	map_open_check(result);
	map_pj_check(result);
	return (result);
}

void	map_open_check(char **map)
{
	int		index;
	int		indexcpy;
	int		i;
	int		icpy;

	index = 0;
	indexcpy = 0;
	i = 0;
	icpy = 0;
	while (map[index] != NULL)
	{
		while (map[index][i] != '\0')
		{
			icpy = i;
			indexcpy = index;
			if (str_cmp(map[indexcpy][icpy], NULL, "02NSEW") == 1
				&& (i == 0 || map[indexcpy][++icpy] == '\0'))
				simple_error("Your map is not closed or there is a wrong character inside");
			icpy = i;
			if (str_cmp(map[indexcpy][icpy], NULL, "02NSEW") == 1
					&& (index == 0 || map[++indexcpy] == NULL))
				simple_error("Your map is not closed or there is a wrong character inside");
			indexcpy = index;
			if (str_cmp(map[indexcpy][icpy], NULL, "02NSEW") == 1
					&& (str_cmp(map[indexcpy][--icpy], NULL, "012NSEW") == 0
					|| str_cmp(map[indexcpy][++icpy], NULL, "012NSEW") == 0))
				simple_error("Your map is not closed or there is a wrong character inside");
			icpy = i;
			if (str_cmp(map[indexcpy][icpy], NULL, "02NSEW") == 1
					&& (str_cmp(map[--indexcpy][icpy], NULL, "012NSEW") == 0
					|| str_cmp(map[++indexcpy][icpy], NULL, "012NSEW") == 0))
				simple_error("Your map is not closed or there is a wrong character inside");
			indexcpy = index;
			i++;
		}
		i = 0;
		index++;
	}
	return ;
}

void	map_pj_check(char **map)
{
	int		pj;
	int		index;
	int		i;

	pj = 0;
	index = 0;
	i = 0;
	while (map[index] != NULL)
	{
		while (map[index][i] != '\0')
		{
			if (str_cmp(map[index][i], NULL, "NSEW") == 1)
				pj++;
			if (pj > 1)
				simple_error("There is more then one player on the map");
			i++;
		}
		i = 0;
		index++;
	}
	if (pj == 0)
		simple_error("There is no player on the map");
	return ;
}

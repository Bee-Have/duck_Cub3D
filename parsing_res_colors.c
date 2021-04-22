/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_res_colors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 14:13:54 by user42            #+#    #+#             */
/*   Updated: 2021/04/22 18:18:13 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	**res_colors_register(char *str, int tab_size)
{
	int		i;
	int		index;
	char	**result;
	char	*tmp;
	
	i = 0;
	index = 0;
	while (str[index] < '0' || str[index] > '9')
		index++;
	tmp = strtrim(str, ft_strlen(str) - index, index);
	result = ft_split((const char *)tmp, " ,");
	free(tmp);
	return (result);
}

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
	map_error_check(result);
	return (result);
}

void	map_error_check(char **map)
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
				simple_error("Your map is not closed");
			icpy = i;
			if (str_cmp(map[indexcpy][icpy], NULL, "02NSEW") == 1
					&& (index == 0 || map[++indexcpy] == NULL))
				simple_error("Your map is not closed");
			indexcpy = index;
			if (str_cmp(map[indexcpy][icpy], NULL, "02NSEW") == 1
					&& (str_cmp(map[indexcpy][--icpy], NULL, "012NSEW") == 0
					|| str_cmp(map[indexcpy][++icpy], NULL, "012NSEW") == 0))
				simple_error("Your map is not closed");
			icpy = i;
			if (str_cmp(map[indexcpy][icpy], NULL, "02NSEW") == 1
					&& (str_cmp(map[--indexcpy][icpy], NULL, "012NSEW") == 0
					|| str_cmp(map[++indexcpy][icpy], NULL, "012NSEW") == 0))
				simple_error("Your map is not closed");
			indexcpy = index;
			i++;
		}
		i = 0;
		index++;
	}
	return ;
}

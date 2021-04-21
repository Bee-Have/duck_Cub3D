/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 14:13:54 by user42            #+#    #+#             */
/*   Updated: 2021/04/21 17:15:44 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	**calc_resolution(char *str, int tab_size)
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
	return (result);
}

char	**map_register(char **file, int *index)
{
	int		i;
	int		length;
	char	**result;

	length = (*index);
	while (file[length] != NULL && str_cmp(0, file[length], "01NSEW") == 1)
		length++;
	length = length - (*index);
	result = (char **)malloc((length + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	result[length] = NULL;
	while (length > 0)
	{
		result[length] =ft_strcpy(file[(*index) + length]);
		length--;
	}
	while (file[(*index)] != NULL && str_cmp(0, file[(*index)], "01NSEW") == 1)
		(*index)++;
	return (result);
}
//here the function(s) for the textures

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 14:13:54 by user42            #+#    #+#             */
/*   Updated: 2021/04/20 17:05:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//replace this with split and then atoi
//more efficient && gain line
//this function will be in charge of calling everyone

int		*calc_resolution(char *str, int tab_size)
{
	int		i;
	int		index;
	int		*result;
	char	*tmp;
	
	i = 0;
	index = 0;
	tmp = ft_strcpy(str);
	tmp = fill_str(tmp, '\0', ft_strlen(tmp));
	result = (int *)malloc(tab_size * sizeof(int));
	if (!result)
		return (NULL);
	while (str[i] != '\0')
	{
		 
		{
			tmp[i - ft_strlen(tmp)] = str[i];
			i++;
		}
		if (index == tab_size && tmp[0] != '\0')
			simple_error();
		if (tmp[0] != '\0')
		{
			result[index] = ft_atoi(tmp);
			index++;
			tmp = fill_str(tmp, '\0', ft_strlen(tmp));
		}
		i++;
	}
	free(tmp);
	return (result);
}

//here the function(s) for the textures

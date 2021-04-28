/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_res_colors_textures.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 14:13:54 by user42            #+#    #+#             */
/*   Updated: 2021/04/28 11:08:35 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3D.h"

char	**res_colors_register(char *str)
{
	int		index;
	char	**result;
	char	*tmp;

	index = 0;
	printf("str[%s]\n", str);
	while (str[index] < '0' || str[index] > '9')
		index++;
	tmp = strtrim(str, ft_strlen(str) - index, index);
	result = ft_split_nums((const char *)tmp);
	print_map(result);
	free(tmp);
	return (result);
}

char	*texture_register(char *str)
{
	int		i;
	int		fd;
	char	*result;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '.')
			break ;
		i++;
	}
	result = strtrim(str, ft_strlen(str) - i, i);
	printf("res[%s]\n", result);
	fd = open(result, O_RDONLY);
	if (fd == -1)
		simple_error("Texture path is incorrect or does not exist");
	else
		close(fd);
	return (result);
}

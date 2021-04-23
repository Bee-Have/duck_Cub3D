/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 12:02:14 by amarini-          #+#    #+#             */
/*   Updated: 2021/04/23 10:20:25 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

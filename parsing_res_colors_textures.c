/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_res_colors_textures.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 14:13:54 by user42            #+#    #+#             */
/*   Updated: 2021/04/29 16:45:58 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3D.h"

void	res_RGB_register(t_cub **cub, char *str)
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
	if ((str[0] == 'R' && result[2] != NULL)
		|| ((str[0] == 'F' || str[0] == 'C') && result[3] != NULL))
		simple_error(cub, "incorect number of argument in '.cub' file");
	if (str[0] == 'R')
	{
		(*cub)->res->width = ft_atoi(result[0]);
		(*cub)->res->height = ft_atoi(result[1]);
	}
	else if (str[0] == 'F' || str[0] == 'C')
	{
		(*cub)->ceiling->R = ft_atoi(result[0]);
		(*cub)->ceiling->G = ft_atoi(result[1]);
		(*cub)->ceiling->B = ft_atoi(result[2]);
	}
	free_2d_array(&result);
}

void	texture_register(t_cub **cub, char *str)
{
	int		i;
	int		fd;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '.')
			break ;
		i++;
	}
	str = strtrim(str, ft_strlen(str) - i, i);
	printf("res[%s]\n", str);
	fd = open(str, O_RDONLY);
	if (fd == -1)
		simple_error(cub, "Texture path is incorrect or does not exist");
	else
		close(fd);
	if (str[0] == 'N' && str[1] == 'O')
		(*cub)->no = str;
	else if (str[0] == 'S' && str[1] == 'O')
		(*cub)->so = str;
	else if (str[0] == 'W' && str[1] == 'E')
		(*cub)->we = str;
	else if (str[0] == 'E' && str[1] == 'A')
		(*cub)->ea = str;
}

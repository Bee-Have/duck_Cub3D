/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_xpm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 08:01:58 by ldutriez          #+#    #+#             */
/*   Updated: 2022/06/28 08:15:01 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	return_result(int fd, char *line, char result)
{
	close(fd);
	free(line);
	get_next_line(-1, NULL);
	return (result);
}

static char	is_size_negative(int fd, char *line, int i)
{
	++i;
	if (ft_atoi(line + i) <= 0)
		return (return_result(fd, line, b_false));
	while (ft_is_digit(line[i]) == b_true)
		++i;
	if (ft_atoi(line + i) <= 0)
		return (return_result(fd, line, b_false));
	return (return_result(fd, line, b_true));
}

char	is_valid_xpm_size(char *path)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(path, O_RDONLY);
	get_next_line(-1, NULL);
	if (fd == -1)
		return (b_false);
	while (get_next_line(fd, &line) == 1)
	{
		i = 0;
		while (line && line[i] != '\0' && line[i] == ' ')
			++i;
		if (line && line[i] == '"')
			return (is_size_negative(fd, line, i));
		free(line);
	}
	free(line);
	close(fd);
	return (b_true);
}

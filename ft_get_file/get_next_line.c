/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:16:18 by amarini-          #+#    #+#             */
/*   Updated: 2021/04/21 14:18:34 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_get_file.h"

int		find_newline(char *str, int read)
{
	int		i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	if (read == 0 && ft_strlen(str) == 0)
		return (i);
	return (-1);
}

int		read_fd(int fd, int *index, char **leftover)
{
	int		result;
	char	*buffer;

	result = 1;
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	while (result > 0 && *index == -1)
	{
		if (!buffer)
			return (-1);
		result = read(fd, buffer, BUFFER_SIZE);
		buffer[result] = '\0';
		*leftover = ft_strjoin(*leftover, buffer);
		*index = find_newline(*leftover, result);
	}
	free(buffer);
	return (result);
}

int		get_next_line(int fd, char **line)
{
	static char		*leftover = NULL;
	int				result;
	int				index;

	index = -1;
	result = 1;
	if (fd < 0 || fd > 256 || BUFFER_SIZE <= 0 || fd == 42 || !line)
		return (-1);
	if (leftover != NULL && leftover[0] != '\0')
		index = find_newline(leftover, 0);
	if (index == -1)
		result = read_fd(fd, &index, &leftover);
	if (index == -1)
		*line = ft_substr(leftover, 0, ft_strlen(leftover), 1);
	else
		*line = ft_substr(leftover, 0, index, 1);
	index++;
	leftover = ft_substr(leftover, index, ft_strlen(leftover) - index, 0);
	if (result == -1 || (result == 0 && ft_strlen(leftover) == 0))
	{
		free(leftover);
		leftover = NULL;
		return (result);
	}
	return (1);
}

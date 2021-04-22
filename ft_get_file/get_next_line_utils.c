/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 11:03:00 by amarini-          #+#    #+#             */
/*   Updated: 2021/04/22 17:31:46 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_get_file.h"

char	*ft_substr(char *str, int start, int len, int line)
{
	int		i;
	char	*result;

	i = 0;
	if (start > ft_strlen(str))
		return (str);
	if (line == 0 && start == 0)
	{
		start = ft_strlen(str) - 1;
		len = 0;
	}
	if (line == 1 && str[start] == '\n')
		start++;
	if (!(result = (char *)malloc((len + 1) * sizeof(char))))
		return (NULL);
	result[len] = '\0';
	while (str[start] != '\0' && i < len)
	{
		result[i] = str[start];
		i++;
		start++;
	}
	if (line == 0)
		free(str);
	return (result);
}

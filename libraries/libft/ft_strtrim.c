/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 13:40:32 by amarini-          #+#    #+#             */
/*   Updated: 2021/04/22 11:56:30 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*strtrim(char *str, int length, int start)
{
	char	*result;
	int		i;

	i = 0;
	if (length == 0)
		result = (char *)malloc(sizeof(char));
	else
		result = (char *)malloc((length + 1) * sizeof(char));
	result[length] = '\0';
	while (i < length)
	{
		result[i] = str[start];
		i++;
		start++;
	}
	return (result);
}
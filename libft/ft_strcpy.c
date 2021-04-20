/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 14:51:37 by user42            #+#    #+#             */
/*   Updated: 2021/04/20 14:55:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *str)
{
	char	*result;
	int		length;
	int		i;
	
	if (!str)
		return (NULL);
	length = ft_strlen(str);
	i = 0;
	result = (char *)malloc((length + 1) * sizeof(char));
	if (!result)
		return (NULL);
	result[length] = '\0';
	while (i < length)
	{
		result[i] = str[i];
		i++;
	}
	return (result);
}

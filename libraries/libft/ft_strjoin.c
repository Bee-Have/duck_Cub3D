/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 17:25:59 by amarini-          #+#    #+#             */
/*   Updated: 2021/04/22 17:33:55 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *dst, char *src)
{
	int		i;
	int		maxlen;
	char	*result;

	i = 0;
	if (!dst || ft_strlen(dst) == 0)
		maxlen = ft_strlen(src);
	else
		maxlen = ft_strlen(dst) + ft_strlen(src);
	result = (char *)malloc((maxlen + 1) * sizeof(char));
	if (!result)
		return (NULL);
	result[maxlen] = '\0';
	if (dst || ft_strlen(dst) != 0)
	{
		result = ft_strncpy(result, dst, i);
		i = ft_strlen(dst);
	}
	result = ft_strncpy(result, src, i);
	free(dst);
	return (result);
}
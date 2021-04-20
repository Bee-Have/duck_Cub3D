/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 14:57:08 by user42            #+#    #+#             */
/*   Updated: 2021/04/20 14:57:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*fill_str(char *str, char fill, int length)
{
	int		i;

	i = 0;
	if (length < 0)
		length = 0;
	str[length] = '\0';
	while (i < length)
	{
		str[i] = fill;
		i++;
	}
	return (str);
}

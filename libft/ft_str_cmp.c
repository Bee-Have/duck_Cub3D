/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_cmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 12:30:55 by amarini-          #+#    #+#             */
/*   Updated: 2021/04/22 18:17:36 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		str_cmp(char c, char *str, char *cmp)
{
	int		i;
	int		j;

	if (!c && !str)
		return (1);
	i = 0;
	j = 0;
	if (c && !str)
	{
		while (cmp[i] != '\0')
		{
			if (cmp[i] == c)
				return (1);
			i++;
		}
	}
	else
		while (str[i] != '\0')
		{
			while (cmp[j] != '\0')
			{
				if (str[i] == cmp[j])
					return (1);
				j++;
			}
			j = 0;
			i++;
		}
	return (0);
}

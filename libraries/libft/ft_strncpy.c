/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncopy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 17:31:57 by amarini-          #+#    #+#             */
/*   Updated: 2021/04/22 17:32:37 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, char *src, int idst)
{
	int		i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[idst] = src[i];
		i++;
		idst++;
	}
	return (dst);
}
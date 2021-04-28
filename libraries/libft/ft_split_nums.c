/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_nums.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 10:41:01 by amarini-          #+#    #+#             */
/*   Updated: 2021/04/28 12:15:17 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		check_non_nums(char c)
{
	if (c < '0' || c > '9')
		return (1);
	return (0);
}

int		calc_row_nums(char const *s)
{
	int		i;
	int		row;

	i = 0;
	row = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && check_non_nums(s[i]) == 1)
			i++;
		if (s[i] != '\0' && check_non_nums(s[i]) == 0)
		{
			row++;
			while (s[i] != '\0' && check_non_nums(s[i]) == 0)
				i++;
		}
	}
	return (row);
}

int		len_nums(char const *s, int strpos)
{
	int		length;

	length = 0;
	while (s[strpos] != '\0')
	{
		if (check_non_nums(s[strpos]) == 1)
		{
			if (length == 0)
				return (1);
			return (length);
		}
		strpos++;
		length++;
	}
	if (length == 0)
		return (1);
	return (length);
}

char	**ft_split_nums(char const *s)
{
	int		i;
	int		irow;
	int		len;
	char	**result;

	if (!s)
		return (NULL);
	irow = 0;
	i = 0;
	result = (char **)malloc((calc_row_nums(s) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	result[calc_row_nums(s)] = NULL;
	while (irow < calc_row_nums(s))
	{
		while (s[i] != '\0' && check_non_nums(s[i]))
			i++;
		len = len_nums(s, i);
		result[irow] = (char *)malloc((len + 1) * sizeof(char));
		if (!result[irow])
			return (free_everything(result));
		result[irow] = fill_str(result[irow], '\0', len);
		while (ft_strlen(result[irow]) < len)
			result[irow][ft_strlen(result[irow])] = s[i++];
		irow++;
	}
	return (result);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 10:21:56 by user42            #+#    #+#             */
/*   Updated: 2021/04/21 16:55:12 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		check_for_sep(char c, char *sep)
{
	int		isep;

	isep = 0;
	while (sep[isep] != '\0')
	{
		if (sep[isep] == c)
			return (1);
		isep++;
	}
	return (0);
}

int		calc_row(char const *s, char *sep)
{
	int		i;
	int		row;

	i = 0;
	row = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && check_for_sep(s[i], sep) == 1)
			i++;
		if (s[i] != '\0' && check_for_sep(s[i], sep) == 0)
		{
			row++;
			while (s[i] != '\0' && check_for_sep(s[i], sep) == 0)
				i++;
		}
	}
	return (row);
}

int		calc_word(char const *s, char *sep, int strpos)
{
	int		length;

	length = 0;
	while (s[strpos] != '\0')
	{
		if (check_for_sep(s[strpos], sep) == 1)
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

char	**free_everything(char **result)
{
	int		irow;

	irow = 0;
	while (result[irow] != NULL)
	{
		free(result[irow]);
		irow++;
	}
	free(result);
	return (NULL);
}

char	**ft_split(char const *s, char *sep)
{
	int		i;
	int		irow;
	char	**result;

	if (!s)
		return (NULL);
	irow = 0;
	i = 0;
	result = (char **)malloc((calc_row(s, sep) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	result[calc_row(s, sep)] = NULL;
	while (irow < calc_row(s, sep))
	{
		while (s[i] != '\0' && check_for_sep(s[i], sep))
			i++;
		result[irow] = (char *)malloc((calc_word(s, sep, i) + 1) * sizeof(char));
		if (!result[irow])
			return (free_everything(result));
		result[irow] = fill_str(result[irow], '\0', calc_word(s, sep, i));
		while (ft_strlen(result[irow]) < calc_word(s, sep, i))
			result[irow][ft_strlen(result[irow])] = s[i++];
		irow++;
	}
	return (result);
}
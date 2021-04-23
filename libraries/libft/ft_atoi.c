/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 14:47:46 by user42            #+#    #+#             */
/*   Updated: 2021/04/20 14:49:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		count_digit(const char *str, int index)
{
	int		i;

	i = 0;
	index += 1;
	while (str[index] != '\0' && (str[index] >= '0' && str[index] <= '9'))
	{
		i++;
		index++;
	}
	return (i);
}

int		convert_res(const char *str, unsigned long int nbr, int index)
{
	unsigned long int	max;

	max = 9223372036854775807;
	if (str[index] == '-' && (nbr > max || count_digit(str, index) > 19))
		return (0);
	else if (nbr > max || count_digit(str, index) > 19)
		return (-1);
	if (str[index] == '-')
		nbr *= -1;
	if (nbr == 1 && count_digit(str, index) >= 3)
		return (0);
	return (nbr);
}

int		ft_atoi(const char *str)
{
	int					i;
	int					index;
	unsigned long int	res;

	i = 0;
	res = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
			|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	index = i;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (convert_res(str, res, index));
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (convert_res(str, res, index));
}
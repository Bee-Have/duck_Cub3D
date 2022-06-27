/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:30:21 by ncoudsi           #+#    #+#             */
/*   Updated: 2022/06/25 21:27:44 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_converts.h"

char	*ft_itoa(long long int nbr)
{
	char	*base;
	char	*result;

	base = "0123456789";
	result = ft_itoa_base(nbr, base);
	return (result);
}

void	ft_itoa_r(char *result, long long int nbr)
{
	char	*base;

	base = "0123456789";
	ft_itoa_base_r(result, nbr, base);
}

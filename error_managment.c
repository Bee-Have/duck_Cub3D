/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_managment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 15:03:10 by user42            #+#    #+#             */
/*   Updated: 2021/04/27 16:18:49 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3D.h"

void	simple_error(char *str)
{
	str = ft_strjoin(ft_strcpy(str), "\n");
	write(1, str, ft_strlen(str));
	exit (1);
}
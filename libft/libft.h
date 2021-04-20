/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 14:42:07 by user42            #+#    #+#             */
/*   Updated: 2021/04/20 15:14:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
#define LIBFT_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int		ft_strlen(char *str);

int		ft_atoi(const char *str);
int		convert_res(const char *str, unsigned long int nbr, int index);
int		count_digit(const char *str, int index);

char	*ft_strcpy(char *str);

char	*fill_str(char *str, char fill, int length);

#endif

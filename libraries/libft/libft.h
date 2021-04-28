/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 14:42:07 by user42            #+#    #+#             */
/*   Updated: 2021/04/28 11:07:36 by amarini-         ###   ########.fr       */
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

char	**ft_split(char const *s, char *sep);
char	**free_everything(char **result);
int		calc_word(char const *s, char *sep, int strpos);
int		calc_row(char const *s, char *sep);
int		check_for_sep(char c, char *sep);

char	**ft_split_nums(char const *s);
int		len_nums(char const *s, int strpos);
int		calc_row_nums(char const *s);
int		check_non_nums(char c);

int		str_cmp(char c, char *str, char *cmp);

char	*strtrim(char *str, int length, int start);

char	*ft_strjoin(char *dst, char *src);

char	*ft_strncpy(char *dst, char *src, int idst);

#endif
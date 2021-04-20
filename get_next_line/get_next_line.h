/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 11:09:46 by amarini-          #+#    #+#             */
/*   Updated: 2021/04/20 16:17:31 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"

int		find_newline(char *str, int read);
int		read_fd(int fd, int *index, char **leftover);
int		get_next_line(int fd, char **line);

char	*ft_strncpy(char *dst, char *src, int idst);
char	*ft_strjoin(char *dst, char *src);
char	*ft_substr(char *str, int start, int len, int line);

#endif

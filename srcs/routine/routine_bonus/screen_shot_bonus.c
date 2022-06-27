/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_shot_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 17:58:34 by ldutriez          #+#    #+#             */
/*   Updated: 2022/06/27 23:37:54 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duckling3d_bonus.h"

static void	set_int_in_char(unsigned char *start, int value)
{
	start[0] = (unsigned char)(value);
	start[1] = (unsigned char)(value >> 8);
	start[2] = (unsigned char)(value >> 16);
	start[3] = (unsigned char)(value >> 24);
}

static int	write_bmp_header(int fd, int filesize)
{
	int				i;
	int				tmp;
	unsigned char	bmpfileheader[54];

	i = 0;
	while (i < 54)
		bmpfileheader[i++] = (unsigned char)(0);
	bmpfileheader[0] = (unsigned char)('B');
	bmpfileheader[1] = (unsigned char)('M');
	set_int_in_char(bmpfileheader + 2, filesize);
	bmpfileheader[10] = (unsigned char)(54);
	bmpfileheader[14] = (unsigned char)(40);
	tmp = W_WIDTH;
	set_int_in_char(bmpfileheader + 18, tmp);
	tmp = W_HEIGHT;
	set_int_in_char(bmpfileheader + 22, tmp);
	bmpfileheader[26] = (unsigned char)(1);
	bmpfileheader[28] = (unsigned char)(24);
	return (!(write(fd, bmpfileheader, 54) < 0));
}

static int	get_color(t_system *sys, int x, int y)
{
	int	color;

	color = *(int *)(sys->mlx.img.addr + (4 * W_WIDTH
				* (W_HEIGHT - 1 - y)) + (4 * x));
	return (color);
}

static int	write_bmp_data(t_system *sys, int fd)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	while (i < W_HEIGHT)
	{
		j = 0;
		while (j < W_WIDTH)
		{
			color = get_color(sys, j, i);
			if (write(fd, &color, 3) < 0)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	save_bmp(t_system *sys)
{
	int			file;
	struct stat	st;
	char		title[35];
	time_t		t;
	struct tm	tm;

	t = time(NULL);
	tm = *localtime(&t);
	sprintf(title, "./screenshots/%d-%02d-%02d-%02d:%02d:%02d.bmp", tm.tm_year
		+ 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	if (stat("./screenshots", &st) == -1)
		mkdir("./screenshots", 0700);
	sys->events.is_f2_pressed = 0;
	file = open(title, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0644);
	if (file < 0)
		return (0);
	if (!write_bmp_header(file, 54 + (3 * W_WIDTH * W_HEIGHT)))
		return (0);
	if (!write_bmp_data(sys, file))
		return (0);
	close(file);
	return (1);
}

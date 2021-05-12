/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_event_manager.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 14:31:17 by amarini-          #+#    #+#             */
/*   Updated: 2021/05/12 10:18:55 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3D.h"

int		key_hook(int keycode, t_vars **vars)
{
	//printf("key [%d] was pressed\n", keycode);
	if (keycode == 65307)
	{
		printf("exiting window\n");
		close_window(vars);
	}
	if (keycode == 32)
		printf("JUMP\n");
}

int		mouse_hook(int button, int x, int y, t_vars **vars)
{
	if (button == 1)
		printf("Left click\n");
	else if (button == 2)
		printf("Middle click (rolly thing)\n");
	else if (button == 3)
		printf("Right click\n");
	else if (button == 4)
		printf("Roll UP\n");
	else if (button == 5)
		printf("Roll DOWN\n");
	else
		printf("button[%d]\n", button);
	printf("pos = [%d][%d]\n", x, y);
}

int		window_hook(t_vars **vars)
{
	printf("window HOOOOOOOK\n");
	return (1);
}

int		mouse_in_window(int x, int y, t_vars **vars)
{
	printf("mouse is in window\n");
	printf("[%d][%d]\n", x, y);
}

int		close_window(t_vars **vars)
{
	mlx_destroy_window((*vars)->mlx, (*vars)->mlx_win);
}

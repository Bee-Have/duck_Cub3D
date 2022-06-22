/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 17:22:27 by amarini-          #+#    #+#             */
/*   Updated: 2022/06/22 19:36:03 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duckling3d_bonus.h"

int	mouse_move(int x, int y, t_system *sys)
{
	int				diff;

	(void)y;
	mlx_mouse_move(sys->mlx.mlx, sys->mlx.win, W_WIDTH / 2, W_HEIGHT / 2);
	diff = W_WIDTH / 2 - x;
	if (diff < 0)
		rotate_player(sys, 'R', MOUSE_SPEED * abs(diff));
	else if (diff > 0)
		rotate_player(sys, 'L', MOUSE_SPEED * abs(diff));
	return (EXIT_SUCCESS);
}

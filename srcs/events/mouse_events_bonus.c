/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 17:22:27 by amarini-          #+#    #+#             */
/*   Updated: 2022/06/21 20:12:57 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duckling3d_bonus.h"

int	mouse_move(int x, int y, t_system *sys)
{
	static t_int2	old_pos = {0, 0};
	int				diff;

	if (old_pos.y == 0 && old_pos.x == 0 && y != 0 && x != 0)
		old_pos = make_int2(y, x);
	diff = old_pos.x - x;
	if (diff < 0)
		rotate_player(sys, 'R', MOUSE_SPEED);
	else if (diff > 0)
		rotate_player(sys, 'L', MOUSE_SPEED);
	old_pos = make_int2(y, x);
	return (EXIT_SUCCESS);
}

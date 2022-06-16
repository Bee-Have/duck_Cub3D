/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duckling3d_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:56:34 by user42            #+#    #+#             */
/*   Updated: 2022/06/16 23:17:45 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DUCKLING3D_H
# define DUCKLING3D_H

# include "cub3d.h"
# include "libft.h"
# include "mlx.h"

# define MOUSE_SPEED 0.02

//* minimap
void	render_pj_minimap(t_system *sys, t_int2 map_start, int pxl_unit);
void	minimap_routine(t_system *sys, int corner);

//* events
int		mouse_move(int x, int y, t_system *sys);

#endif
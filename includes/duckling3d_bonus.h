/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duckling3d_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:56:34 by user42            #+#    #+#             */
/*   Updated: 2022/06/22 19:53:17 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DUCKLING3D_BONUS_H
# define DUCKLING3D_BONUS_H

# include "cub3d.h"
# include "libft.h"
# include "mlx.h"

# define MOUSE_SPEED 0.02

//* minimap
void	render_pj_minimap(t_system *sys, t_int2 pj_pos);
void	minimap_routine(t_system *sys, int corner);

//* minimap general position
# define T_LEFT 0
# define T_RIGHT 1
# define B_LEFT 2
# define B_RIGHT 3
# define CENTER 4
# define TILE_SIZE 32

//* events
int		mouse_move(int x, int y, t_system *sys);

//* keycodes :
# define M 109

#endif
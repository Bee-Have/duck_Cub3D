/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 20:07:59 by ldutriez          #+#    #+#             */
/*   Updated: 2022/05/29 18:32:57 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_texture(t_mlx *mlx, char *line, t_vec2 pos, t_parser *parser)
{
	(void)mlx;
	(void)line;
	(void)pos;
	(void)parser;
}

static unsigned char	get_color_component(char *line, t_vec2 pos
															, t_parser *parser)
{
	int	color_component;

	if (ft_is_digit(line[pos.x]) == b_false
		|| (line[pos.x] == '0' && ft_is_digit(line[pos.x + 1]) == b_true))
	{
		add_error(parser, P_ERR_COLOR, pos.y, pos.x);
		return (0);
	}
	color_component = ft_atoi(line + pos.x);
	if (color_component > 255 || color_component < 0)
		add_error(parser, P_ERR_COLOR, pos.y, pos.x);
	return (color_component);
}

static void	init_color(t_mlx *mlx, char *line, t_vec2 pos, t_parser *parser)
{
	int	r;
	int	g;
	int	b;

	(void)mlx;
	pos.x++;
	while (line[pos.x] != '\0' && line[pos.x] == ' ')
		pos.x++;
	r = get_color_component(line, pos, parser);
	while (line[pos.x] != '\0' && line[pos.x] != ','
		&& ft_is_digit(line[pos.x]) == b_true)
		pos.x++;
	if (line[pos.x] == ',')
		pos.x++;
	g = get_color_component(line, pos, parser);
	while (line[pos.x] != '\0' && line[pos.x] != ',')
		pos.x++;
	if (line[pos.x] == ',')
		pos.x++;
	b = get_color_component(line, pos, parser);
	while (ft_is_digit(line[pos.x]) == b_true)
		pos.x++;
	if (line[pos.x] != '\0')
		add_error(parser, P_ERR_COLOR, pos.y, pos.x);
	printf("color code after parsing: {%d, %d, %d}\n", r, g, b);
}

void	init_config(t_mlx *mlx, char *line, t_vec2 pos, t_parser *parser)
{
	if ((line[pos.x] == 'N' && line[pos.x + 1] == 'O')
		|| (line[pos.x] == 'S' && line[pos.x + 1] == 'O')
		|| (line[pos.x] == 'W' && line[pos.x + 1] == 'E')
		|| (line[pos.x] == 'E' && line[pos.x + 1] == 'A'))
		init_texture(mlx, line, pos, parser);
	else if (line[pos.x] == 'F' || line[pos.x] == 'C')
		init_color(mlx, line, pos, parser);
}

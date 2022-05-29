/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 20:07:59 by ldutriez          #+#    #+#             */
/*   Updated: 2022/05/29 20:37:46 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_texture(t_mlx *mlx, char *line, t_vec2 pos, t_parser *parser)
{
	void	*img;
	// char	*addr;
	t_vec2	size;

	pos.x += 2;
	while (line[pos.x] == ' ')
		pos.x++;
	printf("Current texture path: {%s}\n", line + pos.x);
	if (ft_is_valid_file_path(line + pos.x) == b_false)
		return (add_error(parser, P_ERR_TEXTURE, pos.y, pos.x));
	img = mlx_xpm_file_to_image(mlx->mlx, line + pos.x, &size.x, &size.y);
	// addr = mlx_get_data_addr();
	if (img == NULL)
		add_error(parser, P_ERR_TEXTURE, pos.y, pos.x);
	free(img);	
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

// If color already defined, return.
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
	if ((line[pos.x] == 'N' && line[pos.x + 1] == 'O'
			&& parser->north_texture_count == 1)
		|| (line[pos.x] == 'S' && line[pos.x + 1] == 'O'
			&& parser->south_texture_count == 1)
		|| (line[pos.x] == 'W' && line[pos.x + 1] == 'E'
			&& parser->west_texture_count == 1)
		|| (line[pos.x] == 'E' && line[pos.x + 1] == 'A'
			&& parser->east_texture_count == 1))
		init_texture(mlx, line, pos, parser);
	else if ((line[pos.x] == 'F' && parser->floor_color_count == 1)
		|| (line[pos.x] == 'C' && parser->ceil_color_count == 1))
		init_color(mlx, line, pos, parser);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 20:07:59 by ldutriez          #+#    #+#             */
/*   Updated: 2022/06/24 19:39:03 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_texture(t_system *sys, char *line, t_int2 pos
															, t_parser *parser)
{
	t_img	*texture;

	texture = &sys->s_i.north_texture;
	if (line[pos.x] == 'S' && line[pos.x + 1] == 'O')
		texture = &sys->s_i.south_texture;
	else if (line[pos.x] == 'W' && line[pos.x + 1] == 'E')
		texture = &sys->s_i.west_texture;
	else if (line[pos.x] == 'E' && line[pos.x + 1] == 'A')
		texture = &sys->s_i.east_texture;
	pos.x += 2;
	while (line[pos.x] == ' ')
		pos.x++;
	if (ft_is_valid_file_path(line + pos.x) == b_false)
		return (add_error(parser, P_ERR_TEXTURE, pos.y, pos.x));
	texture->img = mlx_xpm_file_to_image(sys->mlx.mlx, line + pos.x,
			&texture->size.x, &texture->size.y);
	if (texture->img == NULL || is_power_of_two(texture->size.x) == b_false
		|| is_power_of_two(texture->size.y) == b_false)
		add_error(parser, P_ERR_TEXTURE, pos.y, pos.x);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_pxl,
			&texture->line_len, &texture->endian);
	if (texture->addr == NULL)
		add_error(parser, P_ERR_TEXTURE, pos.y, pos.x);
}

static unsigned char	get_color_component(char *line, t_int2 pos
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

static void	init_color(t_system *sys, char *line, t_int2 pos, t_parser *parser)
{
	t_color	*color;

	color = &sys->s_i.floor;
	if (line[pos.x] == 'C')
		color = &sys->s_i.ceiling;
	pos.x++;
	while (line[pos.x] != '\0' && line[pos.x] == ' ')
		pos.x++;
	color->r = get_color_component(line, pos, parser);
	while (line[pos.x] != '\0' && line[pos.x] != ','
		&& ft_is_digit(line[pos.x]) == b_true)
		pos.x++;
	if (line[pos.x] == ',')
		pos.x++;
	color->g = get_color_component(line, pos, parser);
	while (line[pos.x] != '\0' && line[pos.x] != ',')
		pos.x++;
	if (line[pos.x] == ',')
		pos.x++;
	color->b = get_color_component(line, pos, parser);
	while (ft_is_digit(line[pos.x]) == b_true)
		pos.x++;
	if (line[pos.x] != '\0')
		add_error(parser, P_ERR_COLOR, pos.y, pos.x);
	*color = make_color(255, color->r, color->g, color->b);
}

void	init_config(t_system *sys, char *line, t_int2 pos, t_parser *parser)
{
	if ((line[pos.x] == 'N' && line[pos.x + 1] == 'O'
			&& parser->north_texture_count == 1)
		|| (line[pos.x] == 'S' && line[pos.x + 1] == 'O'
			&& parser->south_texture_count == 1)
		|| (line[pos.x] == 'W' && line[pos.x + 1] == 'E'
			&& parser->west_texture_count == 1)
		|| (line[pos.x] == 'E' && line[pos.x + 1] == 'A'
			&& parser->east_texture_count == 1))
		init_texture(sys, line, pos, parser);
	else if ((line[pos.x] == 'F' && parser->floor_color_count == 1)
		|| (line[pos.x] == 'C' && parser->ceil_color_count == 1))
		init_color(sys, line, pos, parser);
}

void	init_map(t_system *sys, t_d_list lines, t_int2 pos, t_parser *parser)
{
	char		**map;
	int			index;

	if (parser->error_count > 0 || lines == NULL)
		return ;
	lines = lines->next;
	map = (char **)malloc(sizeof(char *) * (ft_d_list_size(lines) - pos.y + 1));
	if (map == NULL)
		return ;
	index = 0;
	while (lines != NULL)
	{
		map[index] = (char *)malloc(sizeof(char) * (parser->line_max_size + 1));
		if (map[index] == NULL)
			break ;
		map[index][parser->line_max_size] = '\0';
		ft_strcpy((char *)lines->data, map[index]);
		ft_memset(map[index] + ft_strlen((char *)lines->data), ' ',
			parser->line_max_size - ft_strlen((char *)lines->data));
		lines = lines->next;
		index++;
	}
	sys->s_i.map = map;
	sys->s_i.map_height = index;
	map[index] = NULL;
}

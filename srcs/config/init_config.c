/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 20:07:59 by ldutriez          #+#    #+#             */
/*   Updated: 2022/05/30 16:31:31 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_texture(t_system *sys, char *line, t_int2 pos
															, t_parser *parser)
{
	void	*img;
	t_int2	size;

	pos.x += 2;
	while (line[pos.x] == ' ')
		pos.x++;
	printf("Current texture path: {%s}\n", line + pos.x);
	if (ft_is_valid_file_path(line + pos.x) == b_false)
		return (add_error(parser, P_ERR_TEXTURE, pos.y, pos.x));
	img = mlx_xpm_file_to_image(sys->mlx.mlx, line + pos.x, &size.x, &size.y);
	if (img == NULL)
		add_error(parser, P_ERR_TEXTURE, pos.y, pos.x);
	free(img);
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

// If color already defined, return.
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

void	init_map(t_system *sys, t_d_list lines, t_int2 pos)
{
	int			map_len;
	char		**map;
	int			index;

	(void)sys;
	lines = lines->next;
	map_len = ft_d_list_size(lines) - pos.y;
	map = (char **)malloc(sizeof(char *) * (map_len + 1));
	if (map == NULL)
		return ;
	index = 0;
	while (lines != NULL)
	{
		map[index] = (char *)lines->data;
		lines->data = NULL;
		lines = lines->next;
		index++;
	}
	sys->s_i.map = map;
	map[index] = NULL;
	ft_print_str_tab("Map", map);
}

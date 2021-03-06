/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_content.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 19:09:38 by ldutriez          #+#    #+#             */
/*   Updated: 2022/06/14 20:55:27 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_if_not_last(t_d_list lines, int l, int c, t_parser *parser)
{
	int		index;

	index = 0;
	while (((char *)lines->prev->data)[index] != '\0'
		&& ((char *)lines->prev->data)[index] == ' ')
		++index;
	if ((((char *)lines->prev->data)[index] == '\0' && index != 0)
		|| (((char *)lines->prev->data)[index] == 'N'
			&& ((char *)lines->prev->data)[index + 1] == 'O')
		|| (((char *)lines->prev->data)[index] == 'S'
			&& ((char *)lines->prev->data)[index + 1] == 'O')
		|| (((char *)lines->prev->data)[index] == 'W'
			&& ((char *)lines->prev->data)[index + 1] == 'E')
		|| (((char *)lines->prev->data)[index] == 'E'
			&& ((char *)lines->prev->data)[index + 1] == 'A')
		|| (((char *)lines->prev->data)[index] == 'F')
		|| (((char *)lines->prev->data)[index] == 'C'))
		add_error(parser, P_ERR_UNCLOSED_MAP, l, c);
}

static void	check_enclosing_map(t_d_list lines, int l, int c, t_parser *parser)
{
	if (c == 0
		|| c == (int)ft_strlen((char *)lines->data) - 1
		|| lines->prev == NULL || lines->next == NULL
		|| ((char *)lines->data)[c - 1] == ' '
		|| ((char *)lines->data)[c + 1] == ' '
		|| c >= (int)ft_strlen((char *)lines->prev->data)
		|| ((char *)lines->prev->data)[c] == ' '
		|| c >= (int)ft_strlen((char *)lines->next->data)
		|| ((char *)lines->next->data)[c] == ' ')
		return (add_error(parser, P_ERR_UNCLOSED_MAP, l, c));
	check_if_not_last(lines, l, c, parser);
}

static void	parse_map_line(t_d_list lines, int l, t_parser *parser)
{
	int		i;
	char	*line;

	i = 0;
	line = (char *)lines->data;
	while (line[i] != '\0')
	{
		if (line[i] == '0')
			check_enclosing_map(lines, l, i, parser);
		else if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W'
			|| line[i] == 'E')
		{
			check_enclosing_map(lines, l, i, parser);
			++parser->start_pos_count;
			if (parser->start_pos_count > 1)
				add_error(parser, P_ERR_START_POS, l, i);
		}
		else if (line[i] != ' ' && line[i] != '1')
			add_error(parser, P_ERR_UNVALID_CHAR, l, i);
		i++;
	}
}

static void	update_line_max_size(char *line, t_parser *parser)
{
	if (parser->line_max_size < ft_strlen(line))
		parser->line_max_size = ft_strlen(line);
}

/*
*	Parse the map content.
*	Return the line position of the map.
*/
int	parse_map_content(t_d_list *lines, t_parser *parser)
{
	t_int2	pos;
	char	*line;

	pos.y = ft_d_list_size((*lines)) - 1;
	while ((*lines) != NULL)
	{
		line = (char *)(*lines)->data;
		pos.x = 0;
		if (line[pos.x] == '\0')
			return (pos.y);
		while (line[pos.x] != '\0' && line[pos.x] == ' ')
			++pos.x;
		if ((line[pos.x] == '\0' && pos.x != 0)
			|| (line[pos.x] == 'N' && line[pos.x + 1] == 'O')
			|| (line[pos.x] == 'S' && line[pos.x + 1] == 'O')
			|| (line[pos.x] == 'W' && line[pos.x + 1] == 'E')
			|| (line[pos.x] == 'E' && line[pos.x + 1] == 'A')
			|| (line[pos.x] == 'F') || (line[pos.x] == 'C'))
			return (pos.y);
		parse_map_line((*lines), pos.y, parser);
		update_line_max_size(line, parser);
		--pos.y;
		(*lines) = (*lines)->prev;
	}
	return (pos.y);
}

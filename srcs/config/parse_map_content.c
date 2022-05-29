/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_content.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 19:09:38 by ldutriez          #+#    #+#             */
/*   Updated: 2022/05/26 20:19:42 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

/*
*	Parse the map content.
*	Return the line position of the map.
*/
int	parse_map_content(t_d_list *lines, t_parser *parser)
{
	int			l;
	int			c;
	char		*line;

	l = ft_d_list_size((*lines)) - 1;
	while ((*lines) != NULL)
	{
		line = (char *)(*lines)->data;
		c = 0;
		if (line[c] == '\0')
			return (l);
		while (line[c] != '\0' && line[c] == ' ')
			++c;
		if ((line[c] == '\0' && c != 0)
			|| (line[c] == 'N' && line[c + 1] == 'O')
			|| (line[c] == 'S' && line[c + 1] == 'O')
			|| (line[c] == 'W' && line[c + 1] == 'E')
			|| (line[c] == 'E' && line[c + 1] == 'A')
			|| (line[c] == 'F') || (line[c] == 'C'))
			return (l);
		parse_map_line((*lines), l, parser);
		--l;
		(*lines) = (*lines)->prev;
	}
	return (l);
}

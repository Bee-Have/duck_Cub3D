/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_content.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 19:09:38 by ldutriez          #+#    #+#             */
/*   Updated: 2022/05/24 20:25:17 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	check_enclosing_map(char **lines, int l, int c, t_parser *parser)
{
	int	line_length;
	int	index;

	line_length = ft_strlen(lines[l]);
	index = 0;
	if (c == 0 || c == line_length - 1
		|| l == 0 || l == ft_tab_len((void **)lines) - 1
		|| lines[l][c - 1] == ' ' || lines[l][c + 1] == ' '
		|| c >= (int)ft_strlen(lines[l - 1]) || lines[l - 1][c] == ' '
		|| c >= (int)ft_strlen(lines[l + 1]) || lines[l + 1][c] == ' ')
		return (add_error(parser, P_ERR_UNCLOSED_MAP, l, c));
	while (lines[l - 1][index] != '\0' && lines[l - 1][index] == ' ')
		++index;
	if ((lines[l - 1][index] == '\0' && index != 0)
		|| (lines[l - 1][index] == 'N' && lines[l - 1][index + 1] == 'O')
		|| (lines[l - 1][index] == 'S' && lines[l - 1][index + 1] == 'O')
		|| (lines[l - 1][index] == 'W' && lines[l - 1][index + 1] == 'E')
		|| (lines[l - 1][index] == 'E' && lines[l - 1][index + 1] == 'A')
		|| (lines[l - 1][index] == 'F') || (lines[l - 1][index] == 'C'))
		add_error(parser, P_ERR_UNCLOSED_MAP, l, c);
}

static void	parse_map_line(char **lines, int l, t_parser *parser)
{
	int	i;

	i = 0;
	while (lines[l][i] != '\0')
	{
		if (lines[l][i] == '0')
			check_enclosing_map(lines, l, i, parser);
		else if (lines[l][i] == 'N' || lines[l][i] == 'S' || lines[l][i] == 'W'
			|| lines[l][i] == 'E')
		{
			check_enclosing_map(lines, l, i, parser);
			++parser->start_pos_count;
			if (parser->start_pos_count > 1)
				add_error(parser, P_ERR_START_POS, l, i);
		}
		else if (lines[l][i] != ' ' && lines[l][i] != '1')
			add_error(parser, P_ERR_UNVALID_CHAR, l, i);
		i++;
	}
}

/*
*	Parse the map content.
*	Return the line position of the map.
*/
int	parse_map_content(char **lines, t_parser *parser)
{
	int			l;
	int			c;

	l = ft_tab_len((void **)lines) - 1;
	while (l >= 0)
	{
		c = 0;
		if (lines[l][c] == '\0')
			return (l);
		while (lines[l][c] != '\0' && lines[l][c] == ' ')
			++c;
		if ((lines[l][c] == '\0' && c != 0)
			|| (lines[l][c] == 'N' && lines[l][c + 1] == 'O')
			|| (lines[l][c] == 'S' && lines[l][c + 1] == 'O')
			|| (lines[l][c] == 'W' && lines[l][c + 1] == 'E')
			|| (lines[l][c] == 'E' && lines[l][c + 1] == 'A')
			|| (lines[l][c] == 'F') || (lines[l][c] == 'C'))
			return (l);
		parse_map_line(lines, l, parser);
		--l;
	}
	return (l);
}

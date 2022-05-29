/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:43:25 by ldutriez          #+#    #+#             */
/*   Updated: 2022/05/24 20:35:17 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	add_to_args_count(t_parser *parser, char token, char next_token)
{
	if (token == 'N' && next_token == 'O')
		++parser->north_texture_count;
	else if (token == 'S' && next_token == 'O')
		++parser->south_texture_count;
	else if (token == 'W' && next_token == 'E')
		++parser->west_texture_count;
	else if (token == 'E' && next_token == 'A')
		++parser->east_texture_count;
	else if (token == 'F')
		++parser->floor_color_count;
	else if (token == 'C')
		++parser->ceil_color_count;
}

void	add_error(t_parser *parser, const char *description
	, int line, int column)
{
	int		index;
	char	*tmp;

	if (parser->error_count == ERROR_LIMIT)
		return ;
	ft_strcpy((char *)description, parser->errors[parser->error_count]);
	index = ft_strlen((char *)description);
	tmp = ft_itoa(line + 1);
	ft_strcpy(tmp, parser->errors[parser->error_count] + index);
	index += ft_strlen(tmp);
	free(tmp);
	ft_strcpy(" column ", parser->errors[parser->error_count] + index);
	index += 8;
	tmp = ft_itoa(column + 1);
	ft_strcpy(tmp, parser->errors[parser->error_count] + index);
	index += ft_strlen(tmp);
	free(tmp);
	ft_strcpy("\n", parser->errors[parser->error_count] + index);
	++parser->error_count;
}

int	end_parser(const t_parser *p)
{
	int	index;

	index = 0;
	while (index < p->error_count)
	{
		ft_putstr_fd(2, (char *)p->errors[index]);
		++index;
	}
	if (p->north_texture_count == 0)
		ft_putstr_fd(2, "Error\nNorth texture missing.\n");
	if (p->south_texture_count == 0)
		ft_putstr_fd(2, "Error\nSouth texture missing.\n");
	if (p->west_texture_count == 0)
		ft_putstr_fd(2, "Error\nWest texture missing.\n");
	if (p->east_texture_count == 0)
		ft_putstr_fd(2, "Error\nEast texture missing.\n");
	if (p->floor_color_count == 0)
		ft_putstr_fd(2, "Error\nFloor color missing.\n");
	if (p->ceil_color_count == 0)
		ft_putstr_fd(2, "Error\nCeil color missing.\n");
	if (p->start_pos_count == 0)
		ft_putstr_fd(2, "Error\nStarting position missing.\n");
	return (index + !p->north_texture_count + !p->south_texture_count
		+ !p->west_texture_count + !p->east_texture_count
		+ !p->floor_color_count + !p->ceil_color_count + !p->start_pos_count);
}

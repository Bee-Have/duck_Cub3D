/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:12:32 by amarini-          #+#    #+#             */
/*   Updated: 2022/05/24 17:06:57 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static const char	*g_parser_error_message[] = {
	"Error\nMultiple definition of North texture at line ",
	"Error\nMultiple definition of South texture at line ",
	"Error\nMultiple definition of West texture at line ",
	"Error\nMultiple definition of East texture at line ",
	"Error\nMultiple definition of Floor color at line ",
	"Error\nMultiple definition of Ceiling color at line ",
	"Error\nUnrecognized parameter at line ",
	"Error\nMissing parameter at line ",
	"Error\nMissing map at line ",
	"Error\nUnvalid character at line ",
	"Error\nMultiple definition of start position at line ",
};

/*
*	Check if path is valid and the file is readable.
*	Return 0 on success, 1 on error.
*/
static int	check_path_validity(char *path_to_file)
{
	int	path_length;

	path_length = ft_strlen(path_to_file);
	if (path_length < 5)
	{
		ft_putstr_fd(2, "Error\nFile path is too short.\n");
		return (1);
	}
	if (ft_strcmp(path_to_file + path_length - 4, ".cub") == b_false)
	{
		ft_putstr_fd(2, "Error\nFile extension is not \".cub\".\n");
		return (1);
	}
	if (ft_is_valid_file_path(path_to_file) == b_false)
	{
		ft_putstr_fd(2, "Error\nUnable to open the file.\n");
		return (1);
	}
	return (0);
}

static void	get_data(char *line, int l, int c, t_parser *parser)
{
	add_to_args_count(parser, line[c], line[c + 1]);
	if (line[c] == 'N' && parser->north_texture_count > 1)
		add_error(parser, g_parser_error_message[0], l, c);
	else if (line[c] == 'S' && parser->south_texture_count > 1)
		add_error(parser, g_parser_error_message[1], l, c);
	else if (line[c] == 'W' && parser->west_texture_count > 1)
		add_error(parser, g_parser_error_message[2], l, c);
	else if (line[c] == 'E' && parser->east_texture_count > 1)
		add_error(parser, g_parser_error_message[3], l, c);
	else if (line[c] == 'F' && parser->floor_color_count > 1)
		add_error(parser, g_parser_error_message[4], l, c);
	else if (line[c] == 'C' && parser->ceil_color_count > 1)
		add_error(parser, g_parser_error_message[5], l, c);
	else if (line[c] != 'N' && line[c] != 'S' && line[c] != 'W'
		&& line[c] != 'E' && line[c] != 'F' && line[c] != 'C')
		add_error(parser, g_parser_error_message[6], l, c);
}

static void	parse_map_line(char **lines, int l, t_parser *parser)
{
	int	i;

	i = 0;
	while (lines[l][i] != '\0')
	{
		if (lines[l][i] == ' ' || lines[l][i] == '0' || lines[l][i] == '1')
			;
		else if (lines[l][i] == 'N' || lines[l][i] == 'S' || lines[l][i] == 'W'
			|| lines[l][i] == 'E')
		{
			++parser->starting_pos_count;
			if (parser->starting_pos_count > 1)
				add_error(parser, g_parser_error_message[10], l, i);
		}
		else
			add_error(parser, g_parser_error_message[9], l, i);
		i++;
	}
}

/*
*	Parse the map content.
*	Return the line position of the map.
*/
static int	parse_map_content(char **lines, t_parser *parser)
{
	int			l;
	int			c;

	l = ft_tab_len((void **)lines) - 1;
	(void)parser;
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

static void	parse_lines(char **lines, t_parser *parser)
{
	int			l;
	int			c;

	l = parse_map_content(lines, parser);
	if (lines[l + 1] == NULL)
		add_error(parser, g_parser_error_message[8], l, 0);
	while (l >= 0)
	{
		c = 0;
		while (lines[l][c] != '\0' && lines[l][c] == ' ')
			++c;
		if (lines[l][c] != '\0')
			get_data(lines[l], l, c, parser);
		else if (lines[l][c] == '\0' && c != 0)
			add_error(parser, g_parser_error_message[7], l, c);
		--l;
	}
}

/*
*	Will check if the content of the map is valid.
* A mlx structure will be fill with the parsed data.
* Return 0 on success, otherwise return the number of errors catched.
*/
static int	parse_file_content(t_mlx *mlx, char *path_to_file)
{
	t_parser	parser;
	char		**content;

	(void)mlx;
	ft_bzero(&parser, sizeof(t_parser));
	content = ft_get_file(path_to_file);
	parse_lines(content, &parser);
	ft_print_str_tab("File content", content);
	ft_free_tab((void **)content);
	return (end_parser(&parser));
}

/*
*	Will load the map into the mlx structure if correct.
*	Return 0 on success, otherwise return 1.
*/
int	parse_map(t_mlx *mlx, char *path_to_file)
{
	int			error_count;

	if (check_path_validity(path_to_file) != 0)
		return (1);
	error_count = parse_file_content(mlx, path_to_file);
	if (error_count != 0)
	{
		printf("%d errors generated\n", error_count);
		return (1);
	}
	return (0);
}

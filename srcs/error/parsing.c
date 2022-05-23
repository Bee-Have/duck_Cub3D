/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:12:32 by amarini-          #+#    #+#             */
/*   Updated: 2022/05/23 13:01:06 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static const char	*g_parser_error_message[] = {
	"Error\nRedefinition of North texture at line ",
	"Error\nRedefinition of South texture at line ",
	"Error\nRedefinition of West texture at line ",
	"Error\nRedefinition of East texture at line ",
	"Error\nRedefinition of Floor color at line ",
	"Error\nRedefinition of Ceiling color at line ",
	"Error\nUnrecognized parameter at line ",
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

static void	parse_line(char *line, t_parser *parser)
{
	static int	current_line = 1;
	int			i;

	i = 0;
	while (line && line[i] != '\0' && line[i] == ' ')
		++i;
	if (line && line[i] != '\0')
		get_data(line, current_line, i, parser);
	++current_line;
}

/*
*	Will check if the content of the map is valid.
* A mlx structure will be fill with the parsed data.
* Return 0 on success, otherwise return the number of errors catched.
*/
static int	parse_file_content(t_mlx *mlx, char *path_to_file)
{
	t_parser	parser;
	int			file_fd;
	char		*line;

	(void)mlx;
	ft_bzero(&parser, sizeof(t_parser));
	file_fd = open(path_to_file, O_RDONLY);
	while (get_next_line(file_fd, &line) == b_true)
	{
		parse_line(line, &parser);
		free(line);
	}
	parse_line(line, &parser);
	free(line);
	close(file_fd);
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

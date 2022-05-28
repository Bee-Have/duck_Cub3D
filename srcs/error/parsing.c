/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:12:32 by amarini-          #+#    #+#             */
/*   Updated: 2022/05/26 19:58:29 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	if (line[c] == 'N' && line[c + 1] == 'O' && parser->north_texture_count > 1)
		add_error(parser, P_ERR_NO, l, c);
	else if (line[c] == 'S' && line[c + 1] == 'O'
		&& parser->south_texture_count > 1)
		add_error(parser, P_ERR_SO, l, c);
	else if (line[c] == 'W' && line[c + 1] == 'E'
		&& parser->west_texture_count > 1)
		add_error(parser, P_ERR_WE, l, c);
	else if (line[c] == 'E' && line[c + 1] == 'A'
		&& parser->east_texture_count > 1)
		add_error(parser, P_ERR_EA, l, c);
	else if (line[c] == 'F' && parser->floor_color_count > 1)
		add_error(parser, P_ERR_F, l, c);
	else if (line[c] == 'C' && parser->ceil_color_count > 1)
		add_error(parser, P_ERR_C, l, c);
	else if ((line[c] != 'N' || line[c + 1] != 'O')
		&& (line[c] != 'S' || line[c + 1] != 'O')
		&& (line[c] != 'W' || line[c + 1] != 'E')
		&& (line[c] != 'E' || line[c + 1] != 'A')
		&& line[c] != 'F' && line[c] != 'C')
		add_error(parser, P_ERR_UNKNOWN_PARAM, l, c);
}

static void	parse_lines(t_d_list lines, t_parser *parser)
{
	int			l;
	int			c;
	char		*line;

	l = parse_map_content(&lines, parser);
	if (lines->next == NULL)
		add_error(parser, P_ERR_MISSING_MAP, l, 0);
	while (lines != NULL)
	{
		line = lines->data;
		c = 0;
		while (line[c] != '\0' && line[c] == ' ')
			++c;
		if (line[c] != '\0')
			get_data(line, l, c, parser);
		else if (line[c] == '\0' && c != 0)
			add_error(parser, P_ERR_MISSING_PARAM, l, c);
		--l;
		lines = lines->prev;
	}
}

/*
*	Will check if the content of the map is valid.
*	A mlx structure will be fill with the parsed data.
*	Return 0 on success, otherwise return the number of errors catched.
*/
static int	parse_file_content(t_mlx *mlx, char *path_to_file)
{
	t_parser	parser;
	t_d_list	content;

	(void)mlx;
	ft_bzero(&parser, sizeof(t_parser));
	content = ft_get_file_in_list(path_to_file);
	while (content->next != NULL)
		content = content->next;
	parse_lines(content, &parser);
	while (content->prev != NULL)
		content = content->prev;
	ft_d_list_clear(&content, free);
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

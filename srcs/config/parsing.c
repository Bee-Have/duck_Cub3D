/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:12:32 by amarini-          #+#    #+#             */
/*   Updated: 2022/05/28 20:27:08 by ldutriez         ###   ########.fr       */
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

/*
**	Increment the counter of data crossed for this specific param.
**	Init the correct data in the mlx struct.
**	Add an error to the parser if the data is not valid or if the param is
**	already set.
*/
static void	get_data(t_mlx *mlx, char *line, t_vec2 pos, t_parser *parser)
{
	add_to_args_count(parser, line[pos.x], line[pos.x + 1]);
	init_config(mlx, line, pos, parser);
	if (line[pos.x] == 'N' && line[pos.x + 1] == 'O'
		&& parser->north_texture_count > 1)
		add_error(parser, P_ERR_NO, pos.y, pos.x);
	else if (line[pos.x] == 'S' && line[pos.x + 1] == 'O'
		&& parser->south_texture_count > 1)
		add_error(parser, P_ERR_SO, pos.y, pos.x);
	else if (line[pos.x] == 'W' && line[pos.x + 1] == 'E'
		&& parser->west_texture_count > 1)
		add_error(parser, P_ERR_WE, pos.y, pos.x);
	else if (line[pos.x] == 'E' && line[pos.x + 1] == 'A'
		&& parser->east_texture_count > 1)
		add_error(parser, P_ERR_EA, pos.y, pos.x);
	else if (line[pos.x] == 'F' && parser->floor_color_count > 1)
		add_error(parser, P_ERR_F, pos.y, pos.x);
	else if (line[pos.x] == 'C' && parser->ceil_color_count > 1)
		add_error(parser, P_ERR_C, pos.y, pos.x);
	else if ((line[pos.x] != 'N' || line[pos.x + 1] != 'O')
		&& (line[pos.x] != 'S' || line[pos.x + 1] != 'O')
		&& (line[pos.x] != 'W' || line[pos.x + 1] != 'E')
		&& (line[pos.x] != 'E' || line[pos.x + 1] != 'A')
		&& line[pos.x] != 'F' && line[pos.x] != 'C')
		add_error(parser, P_ERR_UNKNOWN_PARAM, pos.y, pos.x);
}

static void	parse_lines(t_mlx *mlx, t_d_list lines, t_parser *parser)
{
	t_vec2		pos;
	char		*line;

	pos.y = parse_map_content(&lines, parser);
	if (lines->next == NULL)
		add_error(parser, P_ERR_MISSING_MAP, pos.y, 0);
	while (lines != NULL)
	{
		line = lines->data;
		pos.x = 0;
		while (line[pos.x] != '\0' && line[pos.x] == ' ')
			++pos.x;
		if (line[pos.x] != '\0')
			get_data(mlx, line, pos, parser);
		else if (line[pos.x] == '\0' && pos.x != 0)
			add_error(parser, P_ERR_MISSING_PARAM, pos.y, pos.x);
		--pos.y;
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

	ft_bzero(&parser, sizeof(t_parser));
	content = ft_get_file_in_list(path_to_file);
	while (content->next != NULL)
		content = content->next;
	parse_lines(mlx, content, &parser);
	while (content->prev != NULL)
		content = content->prev;
	ft_d_list_clear(&content, free);
	return (end_parser(&parser));
}

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

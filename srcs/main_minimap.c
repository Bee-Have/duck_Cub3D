#include "cub3D.h"

t_img	init_img(void)
{
	t_img	img;

	img.img = NULL;
	img.addr = NULL;
	img.bits_pxl = 0;
	img.line_len = 0;
	img.endian = 0;
	return (img);
}

t_mlx	*init_mlx(int width, int height)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	if (!mlx)
		return (NULL);
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, width, height, "cub3D");
	mlx->img = init_img();
	mlx->img.img = mlx_new_image(mlx->mlx, width, height);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bits_pxl, &mlx->img.line_len
								, &mlx->img.endian);
	return (mlx);
}

t_pos	get_pj_pos(char **map)
{
	t_pos	pj;
	int		row;
	int		col;

	pj.x = -1;
	pj.y = -1;
	row = 0;
	while (map[row] != NULL)
	{
		col = 0;
		while (map[row][col] != '\0')
		{
			if (map[row][col] == 'N' || map[row][col] == 'S'
				|| map[row][col] == 'E' || map[row][col] == 'W')
			{
				pj.y = row;
				pj.x = col;
				return (pj);
			}
			++col;
		}
		++row;
	}
	return (pj);
}

t_pj	init_pj(char **map)
{
	t_pj	pj;

	pj.pos = get_pj_pos(map);
	pj.rot = 0;
	if (map[(int)pj.pos.y][(int)pj.pos.x] == 'N')
		pj.rot = 90;
	else if (map[(int)pj.pos.y][(int)pj.pos.x] == 'S')
		pj.rot = 270;
	else if (map[(int)pj.pos.y][(int)pj.pos.x] == 'E')
		pj.rot = 0;
	else if (map[(int)pj.pos.y][(int)pj.pos.x] == 'W')
		pj.rot = 180;
	return (pj);
}

int	get_map_pxl_unit(t_mlx *mlx)
{
	int	pxl_unit_x;
	int	pxl_unit_y;

	pxl_unit_x = 1920 / ft_strlen(mlx->map[0]);
	pxl_unit_y = 1080 / ft_tab_len((void **)mlx->map);
	if (pxl_unit_x < pxl_unit_y)
		return (pxl_unit_x);
	return (pxl_unit_y);
}

t_color	make_color(unsigned char a, unsigned char r, unsigned char g, unsigned char b)
{
	t_color	color;

	color.a = a;
	color.r = r;
	color.g = g;
	color.b = b;
	color.code = (color.a << 24) + (color.r << 16) + (color.g << 8) + color.b;
	return (color);
}

void	draw_pxl(t_mlx *mlx, t_vec2 pos, t_color color)
{
	int	*tmp;

	if (pos.x < 0 || pos.x > 1920 || pos.y < 0 || pos.y > 1080)
		return ;
	tmp = (int *)mlx->img.addr;
	tmp[(pos.y * 1920) + pos.x] = color.code;
}

void	draw_square(t_mlx *mlx, t_color color, t_vec2 pos, int max)
{
	int		x;
	t_vec2	check;

	x = pos.x;
	check.y = 0;
	while (pos.y < 1080 && check.y < max)
	{
		pos.x = x;
		check.x = 0;
		while (pos.x < 1920 && check.x < max)
		{
			draw_pxl(mlx, pos, color);
			++pos.x;
			++check.x;
		}
		++pos.y;
		++check.y;
	}
}

void	minimap_to_img(t_mlx *mlx)
{
	t_vec2	map;
	t_vec2	addr;
	int		check;
	t_color	color;

	map.y = 0;
	addr.y = 0;
	check = 0;
	while (mlx->map[map.y] != NULL)
	{
		map.x = 0;
		addr.x = 0;
		while (mlx->map[map.y][map.x] != '\0')
		{
			if (mlx->map[map.y][map.x] == '0')
				color = make_color(255, 255, 255, 255);
			else if (mlx->map[map.y][map.x] == '1')
				color = make_color(255, 0, 74, 247);
			else
				color = make_color(255, 255, 110, 110);
			draw_square(mlx, color, addr, mlx->img.pxl_unit);
			addr.x += mlx->img.pxl_unit;
			++map.x;
		}
		addr.y += mlx->img.pxl_unit;
		++map.y;
	}
}

void	switch_vec2(t_vec2 *vector)
{
	int	tmp;

	tmp = (*vector).x;
	(*vector).x = (*vector).y;
	(*vector).y = tmp;
}

//m = slope
void	plot_pxl(t_mlx *mlx, t_vec2 start, t_vec2 end, t_vec2 m, int decide)
{
	t_color	color;
	int		err;
	int		i;
	int		len;

	color = make_color(255, 0, 255, 0);
	err = 2 * m.y - m.x;
	len = 2;
	i = 0;
	while (i < m.x)
	{
		if (start.x < end.x)
			++start.x;
		else
			--start.x;
		if (err < 0)
		{
			if (decide == 1)
			{
				switch_vec2(&start);
				draw_square(mlx, color, start, len);
				switch_vec2(&start);
			}
			else
				draw_square(mlx, color, start, len);
			err = err + 2 * m.y;
		}
		else
		{
			if (start.y < end.y)
				++start.y;
			else
				--start.y;
			if (decide == 1)
			{
				switch_vec2(&start);
				draw_square(mlx, color, start, len);
				switch_vec2(&start);
			}
			else
				draw_square(mlx, color, start, len);
			err = err + 2 * m.y - 2 * m.x;
		}
		//draw_square(mlx, color, start, len);
		++i;
	}
}

//m = slope
void	draw_line(t_mlx *mlx, t_vec2 start, t_vec2 end)
{
	int		dx;
	int		dy;
	t_vec2	m;

	dx = abs(end.x - start.x);
	dy = abs(end.y - start.y);
	m.x = dx;
	m.y = dy;
	if (dx < dy)
	{
		switch_vec2(&start);
		switch_vec2(&end);
		switch_vec2(&m);
		plot_pxl(mlx, start, end, m, 1);
	}
	else
		plot_pxl(mlx, start, end, m, 0);
}

#define LEN 200
#define SPEED 0.1
void	pj_to_img(t_mlx *mlx)
{
	t_color	red;
	t_vec2	pos;
	t_vec2	dir;
	int		size;

	size = 100;
	red = make_color(255, 255, 0, 0);
	pos.y = mlx->pj.pos.y * mlx->img.pxl_unit;
	pos.x = mlx->pj.pos.x * mlx->img.pxl_unit;
	draw_square(mlx, red, pos, size);
	pos.y += size / 2;
	pos.x += size / 2;
	dir.y = pos.y - (LEN * sinf(mlx->pj.rot * (M_PI / 180)));
	dir.x = pos.x - (LEN * cosf(mlx->pj.rot * (M_PI / 180)));
	draw_line(mlx, pos, dir);
}

int	print_all(t_mlx *mlx)
{
	minimap_to_img(mlx);
	pj_to_img(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	return (EXIT_SUCCESS);
}

#define ESC 65307
#define UP 119
#define DOWN 115
#define RIGHT 100
#define LEFT 97
#define R_RIGHT 65363
#define R_LEFT 65361
#define SPEED 0.1
#define R_SPEED 5
int	key_hook(int keycode, t_mlx *mlx)
{
	//printf("code-[%d]\n", keycode);
	if (keycode == ESC)
		mlx_destroy_window(mlx->mlx, mlx->win);

	if (keycode == R_LEFT)
	{
		mlx->pj.rot -= R_SPEED;
		if (mlx->pj.rot < 0)
			mlx->pj.rot = 360 - (mlx->pj.rot * -1);
	}
	else if (keycode == R_RIGHT)
	{
		mlx->pj.rot += R_SPEED;
		if (mlx->pj.rot > 360)
			mlx->pj.rot = 0 + (mlx->pj.rot - 360);
	}
	if (keycode == DOWN)
	{
		mlx->pj.pos.x = mlx->pj.pos.x + (SPEED * cosf(mlx->pj.rot * (M_PI / 180)));
		mlx->pj.pos.y = mlx->pj.pos.y + (SPEED * sinf(mlx->pj.rot * (M_PI / 180)));
	}
	if (keycode == UP)
	{
		mlx->pj.pos.x = mlx->pj.pos.x - (SPEED * cosf(mlx->pj.rot * (M_PI / 180)));
		mlx->pj.pos.y = mlx->pj.pos.y - (SPEED * sinf(mlx->pj.rot * (M_PI / 180)));
	}
	if (keycode == LEFT)
	{
		mlx->pj.pos.x = mlx->pj.pos.x + (SPEED * cosf((mlx->pj.rot + 90) * (M_PI / 180)));
		mlx->pj.pos.y = mlx->pj.pos.y + (SPEED * sinf((mlx->pj.rot + 90) * (M_PI / 180)));
	}
	if (keycode == RIGHT)
	{
		mlx->pj.pos.x = mlx->pj.pos.x + (SPEED * cosf((mlx->pj.rot - 90) * (M_PI / 180)));
		mlx->pj.pos.y = mlx->pj.pos.y + (SPEED * sinf((mlx->pj.rot - 90) * (M_PI / 180)));
	}
	return (EXIT_SUCCESS);
}

void	mlx_routine(t_mlx *mlx)
{
	mlx_loop_hook(mlx->mlx, print_all, mlx);
	//mlx_loop_hook(mlx->mlx, test_line, mlx);
	mlx_hook(mlx->win, 2, 1, key_hook, mlx);
	mlx_loop(mlx->mlx);
}

int	main(int ac, char **av)
{
	t_mlx	*mlx;
	char	**map;

	if (ac != 2)
		return (1);
	map = ft_get_file(av[1]);
	ft_print_str_tab(NULL, map);
	mlx = init_mlx(1920, 1080);
	mlx->map = map;
	mlx->pj = init_pj(mlx->map);
	printf("pxl_unit-[%d]\n", mlx->img.pxl_unit);
	printf("pj-[%f][%f]\n", mlx->pj.pos.y, mlx->pj.pos.x);
	mlx->map[(int)mlx->pj.pos.y][(int)mlx->pj.pos.x] = '0';
	mlx->img.pxl_unit = get_map_pxl_unit(mlx);
	mlx_routine(mlx);
	return (0);
}

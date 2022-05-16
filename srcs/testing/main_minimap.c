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
	mlx->screen.x = width;
	mlx->screen.y = height;
	mlx->event.is_w_pressed = 0;
	mlx->event.is_a_pressed = 0;
	mlx->event.is_s_pressed = 0;
	mlx->event.is_d_pressed = 0;
	mlx->event.is_left_pressed = 0;
	mlx->event.is_right_pressed = 0;
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

void	draw_square(t_mlx *mlx, t_color color, t_vec2 pos, int size)
{
	int		x;
	t_vec2	check;

	x = pos.x;
	check.y = 0;
	while (pos.y < 1080 && check.y < size)
	{
		pos.x = x;
		check.x = 0;
		while (pos.x < 1920 && check.x < size)
		{
			draw_pxl(mlx, pos, color);
			++pos.x;
			++check.x;
		}
		++pos.y;
		++check.y;
	}
}

void	draw_circle(t_mlx *mlx, t_color color, t_vec2 pos, int size)
{
	t_vec2	check;
	t_vec2	center;
	float	dist;
	int		x;

	center.x = pos.x + size / 2;
	center.y = pos.y + size / 2;
	x = pos.x;
	check.y = 0;
	while (pos.y < 1080 && check.y < size)
	{
		pos.x = x;
		check.x = 0;
		while (pos.x < 1920 && check.x < size)
		{
			dist = sqrt((pos.x - center.x) * (pos.x - center.x) +
						(pos.y - center.y) * (pos.y - center.y));
			if (dist < size / 2)
				draw_pxl(mlx, pos, color);
			++pos.x;
			++check.x;
		}
		++pos.y;
		++check.y;
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
	len = 1;
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

#define SPEED 0.1
void	draw_pj(t_mlx *mlx, t_vec2 map_start, int pxl_unit)
{
	t_color	color;
	t_vec2	pos;
	t_vec2	dir;
	int		size;

	size = pxl_unit / 2;
	color = make_color(255, 255, 0, 0);
	pos.x = (map_start.x + (mlx->pj.pos.x * pxl_unit)) + (pxl_unit - size) / 2;
	pos.y = (map_start.y + (mlx->pj.pos.y * pxl_unit)) + (pxl_unit - size) / 2;
	draw_circle(mlx, color, pos, size);
	pos.y += size / 2;
	pos.x += size / 2;
	dir.y = pos.y - (pxl_unit * sinf(mlx->pj.rot * (M_PI / 180)));
	dir.x = pos.x - (pxl_unit * cosf(mlx->pj.rot * (M_PI / 180)));
	draw_line(mlx, pos, dir);
}

void	draw_minimap(t_mlx *mlx, t_vec2 pos, int pxl_unit)
{
	t_color	color;
	t_vec2	imap;
	int		check;
	int		xaddr;

	xaddr = pos.x;
	imap.y = 0;
	check = 0;
	while (mlx->map[imap.y] != NULL)
	{
		imap.x = 0;
		pos.x = xaddr;
		while (mlx->map[imap.y][imap.x] != '\0')
		{
			if (mlx->map[imap.y][imap.x] == '0')
				color = make_color(255, 255, 255, 255);
			else if (mlx->map[imap.y][imap.x] == '1')
				color = make_color(255, 0, 74, 247);
			else
				color = make_color(255, 255, 110, 110);
			draw_square(mlx, color, pos, pxl_unit);
			pos.x += pxl_unit;
			++imap.x;
		}
		pos.y += pxl_unit;
		++imap.y;
	}
}

int	map_pxl_unit(t_vec2 area, char **map)
{
	t_vec2 pxl_unit;

	pxl_unit.x = area.x / ft_strlen(map[0]);
	pxl_unit.y = area.y / ft_tab_len((void **)map);
	if (pxl_unit.x < pxl_unit.y)
		return (pxl_unit.x);
	return (pxl_unit.y);
}

#define T_LEFT 0
#define T_RIGHT 1
#define B_LEFT 2
#define B_RIGHT 3
#define CENTER 4
void	minimap_manager(t_mlx *mlx, int corner)
{
	t_vec2	area_size;
	t_vec2	area_start;
	t_vec2	map_size;
	t_vec2	map_start;
	t_vec2	offset;
	int		pxl_unit;

	if (corner == CENTER)
	{
		area_size.x = mlx->screen.x;
		area_size.y = mlx->screen.y;
	}
	else
	{
		area_size.x = mlx->screen.x / 4;
		area_size.y = mlx->screen.y / 4;
	}
	pxl_unit = map_pxl_unit(area_size, mlx->map);
	map_size.x = ft_strlen(mlx->map[0]) * pxl_unit;
	map_size.y = ft_tab_len((void **)mlx->map) * pxl_unit;
	offset.x = (area_size.x - map_size.x) / 2;
	offset.y = (area_size.y - map_size.y) / 2;
	area_start.x = 0;
	area_start.y = 0;
	if (corner == T_RIGHT)
		area_start.x = mlx->screen.x - area_size.x;
	else if (corner == B_LEFT)
		area_start.y = mlx->screen.y - area_size.y;
	else if (corner == B_RIGHT)
	{
		area_start.x = mlx->screen.x - area_size.x;
		area_start.y = mlx->screen.y - area_size.y;
	}
	map_start.x = area_start.x + offset.x;
	map_start.y = area_start.y + offset.y;
	draw_minimap(mlx, map_start, pxl_unit);
	draw_pj(mlx, map_start, pxl_unit);
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
int	key_press(int keycode, t_mlx *mlx)
{
	//printf("code-[%d]\n", keycode);
	if (keycode == ESC)
		mlx_destroy_window(mlx->mlx, mlx->win);
	if (keycode == R_LEFT)
		mlx->event.is_left_pressed = 1;
	else if (keycode == R_RIGHT)
		mlx->event.is_right_pressed = 1;
	if (keycode == DOWN)
		mlx->event.is_s_pressed = 1;
	if (keycode == UP)
		mlx->event.is_w_pressed = 1;
	if (keycode == LEFT)
		mlx->event.is_a_pressed = 1;
	if (keycode == RIGHT)
		mlx->event.is_d_pressed = 1;
	return (EXIT_SUCCESS);
}

int	key_release(int keycode, t_mlx *mlx)
{
	if (keycode == R_LEFT)
		mlx->event.is_left_pressed = 0;
	else if (keycode == R_RIGHT)
		mlx->event.is_right_pressed = 0;
	if (keycode == DOWN)
		mlx->event.is_s_pressed = 0;
	if (keycode == UP)
		mlx->event.is_w_pressed = 0;
	if (keycode == LEFT)
		mlx->event.is_a_pressed = 0;
	if (keycode == RIGHT)
		mlx->event.is_d_pressed = 0;
	return (EXIT_SUCCESS);
}

int	update_keys_events(t_mlx *mlx)
{
	if (mlx->event.is_left_pressed == 1)
	{
		mlx->pj.rot -= R_SPEED;
		if (mlx->pj.rot < 0)
			mlx->pj.rot = 360 - (mlx->pj.rot * -1);
	}
	if (mlx->event.is_right_pressed == 1)
	{
		mlx->pj.rot += R_SPEED;
		if (mlx->pj.rot > 360)
			mlx->pj.rot = 0 + (mlx->pj.rot - 360);
	}
	if (mlx->event.is_s_pressed == 1)
	{
		mlx->pj.pos.x = mlx->pj.pos.x + (SPEED * cosf(mlx->pj.rot * (M_PI / 180)));
		mlx->pj.pos.y = mlx->pj.pos.y + (SPEED * sinf(mlx->pj.rot * (M_PI / 180)));
	}
	if (mlx->event.is_w_pressed == 1)
	{
		mlx->pj.pos.x = mlx->pj.pos.x - (SPEED * cosf(mlx->pj.rot * (M_PI / 180)));
		mlx->pj.pos.y = mlx->pj.pos.y - (SPEED * sinf(mlx->pj.rot * (M_PI / 180)));
	}
	if (mlx->event.is_a_pressed == 1)
	{
		mlx->pj.pos.x = mlx->pj.pos.x + (SPEED * cosf((mlx->pj.rot + 90) * (M_PI / 180)));
		mlx->pj.pos.y = mlx->pj.pos.y + (SPEED * sinf((mlx->pj.rot + 90) * (M_PI / 180)));
	}
	if (mlx->event.is_d_pressed == 1)
	{
		mlx->pj.pos.x = mlx->pj.pos.x + (SPEED * cosf((mlx->pj.rot - 90) * (M_PI / 180)));
		mlx->pj.pos.y = mlx->pj.pos.y + (SPEED * sinf((mlx->pj.rot - 90) * (M_PI / 180)));
	}
	return (EXIT_SUCCESS);
}

int	update_all(t_mlx *mlx)
{
	update_keys_events(mlx);
	minimap_manager(mlx, CENTER);
	// minimap_manager(mlx, T_LEFT);
	// minimap_manager(mlx, T_RIGHT);
	// minimap_manager(mlx, B_LEFT);
	// minimap_manager(mlx, B_RIGHT);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	return (EXIT_SUCCESS);
}

void	mlx_routine(t_mlx *mlx)
{
	mlx_loop_hook(mlx->mlx, update_all, mlx);
	mlx_hook(mlx->win, 2, 1L<<0, key_press, mlx);
	mlx_hook(mlx->win, 3, 1L<<1, key_release, mlx);
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
	printf("pj-[%f][%f]\n", mlx->pj.pos.y, mlx->pj.pos.x);
	mlx->map[(int)mlx->pj.pos.y][(int)mlx->pj.pos.x] = '0';
	mlx_routine(mlx);
	return (0);
}

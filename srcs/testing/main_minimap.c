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

t_event	init_events(void)
{
	t_event	events;
	
	events.is_w_pressed = 0;
	events.is_a_pressed = 0;
	events.is_s_pressed = 0;
	events.is_d_pressed = 0;
	events.is_left_pressed = 0;
	events.is_right_pressed = 0;
	return (events);
}

t_mlx	init_mlx(int width, int height)
{
	t_mlx	mlx;

	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, width, height, "cub3D");
	mlx.img = init_img();
	mlx.img.img = mlx_new_image(mlx.mlx, width, height);
	mlx.img.addr = mlx_get_data_addr(mlx.img.img, &mlx.img.bits_pxl, &mlx.img.line_len
								, &mlx.img.endian);
	return (mlx);
}

t_vec2	get_pj_pos(char **map)
{
	t_vec2	pj;
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
		pj.rot = 180;
	else if (map[(int)pj.pos.y][(int)pj.pos.x] == 'W')
		pj.rot = 0;
	pj.dir.x = pj.pos.x - (SPEED * cosf(pj.rot * (M_PI / 180)));
	pj.dir.y = pj.pos.y - (SPEED * sinf(pj.rot * (M_PI / 180)));
	pj.plane.x = 0;
	pj.plane.y = 0.1;
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

void	draw_pxl(t_system *sys, t_int2 pos, t_color color)
{
	int	*tmp;

	if (pos.x < 0 || pos.x > 1920 || pos.y < 0 || pos.y > 1080)
		return ;
	tmp = (int *)sys->mlx.img.addr;
	tmp[(pos.y * 1920) + pos.x] = color.code;
}

void	draw_square(t_system *sys, t_color color, t_int2 pos, int size)
{
	int		x;
	t_int2	check;

	x = pos.x;
	check.y = 0;
	while (pos.y < 1080 && check.y < size)
	{
		pos.x = x;
		check.x = 0;
		while (pos.x < 1920 && check.x < size)
		{
			draw_pxl(sys, pos, color);
			++pos.x;
			++check.x;
		}
		++pos.y;
		++check.y;
	}
}

void	draw_circle(t_system *sys, t_color color, t_int2 pos, int size)
{
	t_int2	check;
	t_int2	center;
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
				draw_pxl(sys, pos, color);
			++pos.x;
			++check.x;
		}
		++pos.y;
		++check.y;
	}
}

void	switch_vec2(t_int2 *vector)
{
	int	tmp;

	tmp = (*vector).x;
	(*vector).x = (*vector).y;
	(*vector).y = tmp;
}

//m = slope
void	plot_pxl(t_system *sys, t_int2 start, t_int2 end, t_int2 m, int decide, t_color color)
{
	// t_color	color;
	int		err;
	int		i;
	int		len;

	// color = make_color(255, 0, 255, 0);
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
				draw_square(sys, color, start, len);
				switch_vec2(&start);
			}
			else
				draw_square(sys, color, start, len);
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
				draw_square(sys, color, start, len);
				switch_vec2(&start);
			}
			else
				draw_square(sys, color, start, len);
			err = err + 2 * m.y - 2 * m.x;
		}
		++i;
	}
}

//m = slope
void	draw_line(t_system *sys, t_int2 start, t_int2 end, t_color color)
{
	int		dx;
	int		dy;
	t_int2	m;

	dx = abs(end.x - start.x);
	dy = abs(end.y - start.y);
	m.x = dx;
	m.y = dy;
	if (dx < dy)
	{
		switch_vec2(&start);
		switch_vec2(&end);
		switch_vec2(&m);
		plot_pxl(sys, start, end, m, 1, color);
	}
	else
		plot_pxl(sys, start, end, m, 0, color);
}

void	raycasting_routine(t_system *sys, t_int2 map_start)
{
	t_color	color;
	int		x;
	double	camera_x;
	t_vec2	ray_dir;
	t_vec2	map;
	t_vec2	side_dist;
	t_vec2	delta_dist;
	double	perp_wall_dist;
	t_int2	step;
	int		hit;
	int		side;

	x = 0;
	while (x < sys->s_i.screen.x)
	{
		map.x = (int)sys->pj.pos.x;
		map.y = (int)sys->pj.pos.y;
		hit = 0;
		camera_x = 2 * x / (double)sys->s_i.screen.x - 1;
		ray_dir.x = (sys->pj.dir.x - sys->pj.pos.x) + sys->pj.plane.x * camera_x;
		ray_dir.y = (sys->pj.dir.y - sys->pj.pos.y) + sys->pj.plane.y * camera_x;
		if (ray_dir.x == 0)
			delta_dist.x = 1e30;
		else
			delta_dist.x = fabs(1 / ray_dir.x);
		if (ray_dir.y == 0)
			delta_dist.y = 1e30;
		else
			delta_dist.y = fabs(1 / ray_dir.y);
		if (ray_dir.x < 0)
		{
			step.x = -1;
			side_dist.x = (sys->pj.pos.x - map.x) * delta_dist.x;
		}
		else
		{
			step.x = 1;
			side_dist.x = (map.x + 1.0 - sys->pj.pos.x) * delta_dist.x;
		}
		if (ray_dir.y < 0)
		{
			step.y = -1;
			side_dist.y = (sys->pj.pos.y - map.y) * delta_dist.y;
		}
		else
		{
			step.y = 1;
			side_dist.y = (map.y + 1.0 - sys->pj.pos.y) * delta_dist.y;
		}

		while (hit == 0)
		{
			if (side_dist.x < side_dist.y)
			{
				side_dist.x += delta_dist.x;
				map.x += step.x;
				side = 0;
			}
			else
			{
				side_dist.y += delta_dist.y;
				map.y += step.y;
				side = 1;
			}
			//! the map will not always be square/rectangular
			if ((int)map.y < 0 || (int)map.y > ft_tab_len((void **)sys->s_i.map)
				|| (int)map.x < 0 || (int)map.x > (int)ft_strlen(sys->s_i.map[0])
				|| sys->s_i.map[(int)map.y][(int)map.x] == '1')
			{
				t_int2	start;
				t_int2	end;
				int		size;
								
				// drawing general ray
				size = sys->s_i.pxl_unit / 2;
				start.x = (map_start.x + (sys->pj.pos.x * sys->s_i.pxl_unit)) + size;
				start.y = (map_start.y + (sys->pj.pos.y * sys->s_i.pxl_unit)) + size;
				end.x = (map_start.x + (map.x * sys->s_i.pxl_unit)) + size;
				end.y = (map_start.y + (map.y * sys->s_i.pxl_unit)) + size;
				color = make_color(255, 0, 0, 0);
				draw_line(sys, start, end, color);
				// drawing camera plane
				size = sys->s_i.pxl_unit / 2;
				start.x = (map_start.x + ((sys->pj.dir.x + sys->pj.plane.x) * sys->s_i.pxl_unit)) + size;
				start.y = (map_start.y + ((sys->pj.dir.y + sys->pj.plane.y) * sys->s_i.pxl_unit)) + size;
				end.x = (map_start.x + ((sys->pj.dir.x - sys->pj.plane.x) * sys->s_i.pxl_unit)) + size;
				end.y = (map_start.y + ((sys->pj.dir.y - sys->pj.plane.y) * sys->s_i.pxl_unit)) + size;
				color = make_color(255, 0, 255, 0);
				draw_line(sys, start, end, color);
				hit = 1;

				int		line_height;
				int		draw_start;
				int		draw_end;

				if (side == 0)
					perp_wall_dist = side_dist.x - delta_dist.x;
				else
					perp_wall_dist = side_dist.y - delta_dist.y;
				line_height = (int)(sys->s_i.screen.y / perp_wall_dist);
				draw_start = -line_height / 2 + sys->s_i.screen.y / 2;
				if (draw_start < 0)
					draw_start = 0;
				draw_end = line_height / 2 + sys->s_i.screen.y / 2;
				if (draw_end >= sys->s_i.screen.y)
					draw_end = sys->s_i.screen.y - 1;

				start.x = x;
				end.x = x;
				color = make_color(255, 0, 0, 255); // blue
				start.y = 0;
				end.y = draw_start;
				draw_line(sys, start, end, color);
				color = make_color(255, 255, 255, 255); // white
				start.y = draw_end;
				end.y = sys->s_i.screen.y;
				draw_line(sys, start, end, color);
				if (side == 1)
					color = make_color(255, 255, 0, 0); // red
				else
					color = make_color(255, 0, 255, 0); // greed
				start.y = draw_start;
				end.y = draw_end;
				draw_line(sys, start, end, color);
			}
		}
		++x;
	}
}

#define SPEED 0.1
void	draw_pj(t_system *sys, t_int2 map_start, int pxl_unit)
{
	t_color	color;
	t_int2	pos;
	t_int2	dir;
	int		size;

	size = pxl_unit / 2;
	color = make_color(255, 255, 0, 0);
	pos.x = (map_start.x + (sys->pj.pos.x * pxl_unit)) + (pxl_unit - size) / 2;
	pos.y = (map_start.y + (sys->pj.pos.y * pxl_unit)) + (pxl_unit - size) / 2;
	draw_circle(sys, color, pos, size);
	pos.y += size / 2;
	pos.x += size / 2;
	dir.y = pos.y - (pxl_unit * sinf(sys->pj.rot * (M_PI / 180)));
	dir.x = pos.x - (pxl_unit * cosf(sys->pj.rot * (M_PI / 180)));
	printf("pj-[%d][%d]\n", pos.y, pos.x);
	color = make_color(255, 0, 255, 0);
	draw_line(sys, pos, dir, color);
}

void	draw_minimap(t_system *sys, t_int2 pos, int pxl_unit)
{
	t_color	color;
	t_int2	imap;
	int		xaddr;

	xaddr = pos.x;
	imap.y = 0;
	while (sys->s_i.map[imap.y] != NULL)
	{
		imap.x = 0;
		pos.x = xaddr;
		while (sys->s_i.map[imap.y][imap.x] != '\0')
		{
			if (sys->s_i.map[imap.y][imap.x] == '0')
				color = make_color(255, 255, 255, 255);
			else if (sys->s_i.map[imap.y][imap.x] == '1')
				color = make_color(255, 0, 74, 247);
			else
				color = make_color(255, 255, 110, 110);
			draw_square(sys, color, pos, pxl_unit);
			pos.x += pxl_unit;
			++imap.x;
		}
		pos.y += pxl_unit;
		++imap.y;
	}
}

int	map_pxl_unit(t_int2 area, char **map)
{
	t_int2 pxl_unit;

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
void	minimap_manager(t_system *sys, int corner)
{
	t_int2	area_size;
	t_int2	area_start;
	t_int2	map_size;
	t_int2	map_start;
	t_int2	offset;

	if (corner == CENTER)
	{
		area_size.x = sys->s_i.screen.x;
		area_size.y = sys->s_i.screen.y;
	}
	else
	{
		area_size.x = sys->s_i.screen.x / 4;
		area_size.y = sys->s_i.screen.y / 4;
	}
	if (sys->s_i.pxl_unit == 0)
		sys->s_i.pxl_unit = map_pxl_unit(area_size, sys->s_i.map);
	map_size.x = ft_strlen(sys->s_i.map[0]) * sys->s_i.pxl_unit;
	map_size.y = ft_tab_len((void **)sys->s_i.map) * sys->s_i.pxl_unit;
	offset.x = (area_size.x - map_size.x) / 2;
	offset.y = (area_size.y - map_size.y) / 2;
	area_start.x = 0;
	area_start.y = 0;
	if (corner == T_RIGHT)
		area_start.x = sys->s_i.screen.x - area_size.x;
	else if (corner == B_LEFT)
		area_start.y = sys->s_i.screen.y - area_size.y;
	else if (corner == B_RIGHT)
	{
		area_start.x = sys->s_i.screen.x - area_size.x;
		area_start.y = sys->s_i.screen.y - area_size.y;
	}
	map_start.x = area_start.x + offset.x;
	map_start.y = area_start.y + offset.y;
	draw_minimap(sys, map_start, sys->s_i.pxl_unit);
	draw_pj(sys, map_start, sys->s_i.pxl_unit);
	raycasting_routine(sys, map_start);
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
int	key_press(int keycode, t_system *sys)
{
	//printf("code-[%d]\n", keycode);
	if (keycode == ESC)
		mlx_destroy_window(sys->mlx.mlx, sys->mlx.win);
	if (keycode == R_LEFT)
		sys->events.is_left_pressed = 1;
	else if (keycode == R_RIGHT)
		sys->events.is_right_pressed = 1;
	if (keycode == DOWN)
		sys->events.is_s_pressed = 1;
	if (keycode == UP)
		sys->events.is_w_pressed = 1;
	if (keycode == LEFT)
		sys->events.is_a_pressed = 1;
	if (keycode == RIGHT)
		sys->events.is_d_pressed = 1;
	return (EXIT_SUCCESS);
}

int	key_release(int keycode, t_system *sys)
{
	if (keycode == R_LEFT)
		sys->events.is_left_pressed = 0;
	else if (keycode == R_RIGHT)
		sys->events.is_right_pressed = 0;
	if (keycode == DOWN)
		sys->events.is_s_pressed = 0;
	if (keycode == UP)
		sys->events.is_w_pressed = 0;
	if (keycode == LEFT)
		sys->events.is_a_pressed = 0;
	if (keycode == RIGHT)
		sys->events.is_d_pressed = 0;
	return (EXIT_SUCCESS);
}

int	update_keys_events(t_system *sys)
{
	double	old_plane_x;

	if (sys->events.is_left_pressed == 1)
	{
		sys->pj.rot -= R_SPEED;
		if (sys->pj.rot < 0)
			sys->pj.rot = 360 - (sys->pj.rot * -1);
		old_plane_x = sys->pj.plane.x;
		sys->pj.plane.x = sys->pj.plane.x * cos(-R_SPEED * (M_PI / 180)) - sys->pj.plane.y * sin(-R_SPEED * (M_PI / 180));
		sys->pj.plane.y = old_plane_x * sin(-R_SPEED * (M_PI / 180)) + sys->pj.plane.y * cos(-R_SPEED * (M_PI / 180));
	}
	if (sys->events.is_right_pressed == 1)
	{
		sys->pj.rot += R_SPEED;
		if (sys->pj.rot > 360)
			sys->pj.rot = 0 + (sys->pj.rot - 360);
		old_plane_x = sys->pj.plane.x;
		sys->pj.plane.x = sys->pj.plane.x * cos(R_SPEED * (M_PI / 180)) - sys->pj.plane.y * sin(R_SPEED * (M_PI / 180));
		sys->pj.plane.y = old_plane_x * sin(R_SPEED * (M_PI / 180)) + sys->pj.plane.y * cos(R_SPEED * (M_PI / 180));
	}
	if (sys->events.is_s_pressed == 1)
	{
		sys->pj.pos.x = sys->pj.pos.x + (SPEED * cosf(sys->pj.rot * (M_PI / 180)));
		sys->pj.pos.y = sys->pj.pos.y + (SPEED * sinf(sys->pj.rot * (M_PI / 180)));
	}
	if (sys->events.is_w_pressed == 1)
	{
		sys->pj.pos.x = sys->pj.pos.x - (SPEED * cosf(sys->pj.rot * (M_PI / 180)));
		sys->pj.pos.y = sys->pj.pos.y - (SPEED * sinf(sys->pj.rot * (M_PI / 180)));
	}
	if (sys->events.is_a_pressed == 1)
	{
		sys->pj.pos.x = sys->pj.pos.x + (SPEED * cosf((sys->pj.rot + 90) * (M_PI / 180)));
		sys->pj.pos.y = sys->pj.pos.y + (SPEED * sinf((sys->pj.rot + 90) * (M_PI / 180)));
	}
	if (sys->events.is_d_pressed == 1)
	{
		sys->pj.pos.x = sys->pj.pos.x + (SPEED * cosf((sys->pj.rot - 90) * (M_PI / 180)));
		sys->pj.pos.y = sys->pj.pos.y + (SPEED * sinf((sys->pj.rot - 90) * (M_PI / 180)));
	}
	sys->pj.dir.x = sys->pj.pos.x - (SPEED * cosf(sys->pj.rot * (M_PI / 180)));
	sys->pj.dir.y = sys->pj.pos.y - (SPEED * sinf(sys->pj.rot * (M_PI / 180)));
	return (EXIT_SUCCESS);
}

int	update_all(t_system *sys)
{
	update_keys_events(sys);
	// minimap_manager(sys, CENTER);
	minimap_manager(sys, T_LEFT);
	// minimap_manager(sys, T_RIGHT);
	// minimap_manager(sys, B_LEFT);
	// minimap_manager(sys, B_RIGHT);
	mlx_put_image_to_window(sys->mlx.mlx, sys->mlx.win, sys->mlx.img.img, 0, 0);
	return (EXIT_SUCCESS);
}

void	mlx_routine(t_system *sys)
{
	mlx_loop_hook(sys->mlx.mlx, update_all, sys);
	mlx_hook(sys->mlx.win, 2, 1L<<0, key_press, sys);
	mlx_hook(sys->mlx.win, 3, 1L<<1, key_release, sys);
	mlx_loop(sys->mlx.mlx);
}

int	main(int ac, char **av)
{
	t_system		*sys;
	t_screen_info	s_i;

	if (ac != 2)
		return (EXIT_FAILURE);
	sys = (t_system *)malloc(sizeof(t_system));
	if (!sys)
		return (EXIT_FAILURE);
	s_i.map = ft_get_file(av[1]);
	ft_print_str_tab(NULL, s_i.map);
	sys->mlx = init_mlx(1920, 1080);
	sys->s_i = s_i;
	sys->s_i.pxl_unit = 0;
	sys->s_i.screen.x = 1920;
	sys->s_i.screen.y = 1080;
	sys->events = init_events();
	sys->pj = init_pj(sys->s_i.map);
	printf("pj-[%f][%f]\n", sys->pj.pos.y, sys->pj.pos.x);
	sys->s_i.map[(int)sys->pj.pos.y][(int)sys->pj.pos.x] = '0';
	mlx_routine(sys);
	return (0);
}

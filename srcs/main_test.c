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
	pj.dir.x = 0.00000000000;
	pj.dir.y = 0.00000000000;
	if (map[(int)pj.pos.y][(int)pj.pos.x] == 'N')
		pj.dir.y = -0.1;
	else if (map[(int)pj.pos.y][(int)pj.pos.x] == 'S')
		pj.dir.y = 0.1;
	else if (map[(int)pj.pos.y][(int)pj.pos.x] == 'E')
		pj.dir.x = 0.1;
	else if (map[(int)pj.pos.y][(int)pj.pos.x] == 'W')
		pj.dir.x = -0.1;
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

void	minimap_to_img(t_mlx *mlx)
{
	t_vec2	map;
	t_vec2	addr;
	t_vec2	check;
	t_color	color;
	char	*tmp;

	map.y = 0;
	addr.y = 0;
	check.y = 0;
	while (mlx->map[map.y] != NULL)
	{
		map.x = 0;
		addr.x = 0;
		check.x = 0;
		while (mlx->map[map.y][map.x] != '\0')
		{
			if (mlx->map[map.y][map.x] == '0')
				color = make_color(255, 255, 255, 255);
			else if (mlx->map[map.y][map.x] == '1')
				color = make_color(255, 0, 74, 247);
			else
				color = make_color(255, 255, 110, 110);
			tmp = mlx->img.addr + ((addr.y * 1920) + addr.x);
			*(unsigned int *)tmp = color.code;
			addr.x += 4;
			check.x += 4;
			if (check.x >= mlx->img.pxl_unit * 4)
			{
				check.x = 0;
				++map.x;
			}
		}
		addr.y += 4;
		check.y += 4;
		if (check.y >= mlx->img.pxl_unit * 4)
		{
			check.y = 0;
			++map.y;
		}
	}
}

void	pj_to_img(t_mlx *mlx)
{
	t_color	color;
	t_vec2	addr;
	t_pos	test;
	t_vec2	check;
	char	*tmp;

	color = make_color(255, 255, 0, 0);
	test.y = ((mlx->pj.pos.y * mlx->img.pxl_unit) + (mlx->img.pxl_unit / 2)) * 4;
	test.x = ((mlx->pj.pos.x * mlx->img.pxl_unit) + (mlx->img.pxl_unit / 2)) * 4;
	addr.y = (((int)mlx->pj.pos.y * mlx->img.pxl_unit) + (mlx->img.pxl_unit / 2)) * 4;
	addr.x = (((int)mlx->pj.pos.x * mlx->img.pxl_unit) + (mlx->img.pxl_unit / 2)) * 4;
	while (addr.y < test.y)
		addr.y += 4;
	while (addr.x < test.x)
		addr.x += 4;
	check.y = 0;
	while (check.y < mlx->img.pxl_unit / 2)
	{
		addr.x = ((mlx->pj.pos.x * mlx->img.pxl_unit) + (mlx->img.pxl_unit / 2)) * 4;
		check.x = 0;
		while (check.x < mlx->img.pxl_unit / 2)
		{
			tmp = mlx->img.addr + ((addr.y * 1920) + addr.x);
			*(unsigned int *)tmp = color.code;
			addr.x += 4;
			check.x += 4;
		}
		addr.y += 4;
		check.y += 4;
	}
}

int	print_all(t_mlx *mlx)
{
	minimap_to_img(mlx);
	pj_to_img(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	return (EXIT_SUCCESS);
}

//esc = 65307
//N-up-front = 65362
//S-down-back = 65364
//E-right = 65363
//W-left = 65361
int	key_hook(int keycode, t_mlx *mlx)
{
	(void)mlx;
	//printf("code-[%d]\n", keycode);
	if (keycode == 65307)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
	}
	if (keycode == 65362)
	{
		if (mlx->pj.dir.y > 0.0000000000 || mlx->pj.dir.y < 0.0000000000)
			mlx->pj.pos.y += mlx->pj.dir.y;
		else if (mlx->pj.dir.x > 0.0000000000 || mlx->pj.dir.x < 0.0000000000)
			mlx->pj.pos.x += mlx->pj.dir.x;
	}
	if (keycode == 65364)
	{
		if (mlx->pj.dir.y > 0.0000000000 || mlx->pj.dir.y < 0.0000000000)
			mlx->pj.pos.y -= mlx->pj.dir.y;
		else if (mlx->pj.dir.x > 0.0000000000 || mlx->pj.dir.x < 0.0000000000)
			mlx->pj.pos.x -= mlx->pj.dir.x;
	}
	if (keycode == 65363)
	{
		if (mlx->pj.dir.x > 0.0000000000)
			mlx->pj.pos.y -= mlx->pj.dir.y + 0.1;
		else if (mlx->pj.dir.x < 0.0000000000)
			mlx->pj.pos.y -= mlx->pj.dir.y - 0.1;
		else if (mlx->pj.dir.y > 0.0000000000)
			mlx->pj.pos.x -= mlx->pj.dir.x + 0.1;
		else if (mlx->pj.dir.y < 0.0000000000)
			mlx->pj.pos.x -= mlx->pj.dir.x - 0.1;
	}
	if (keycode == 65361)
	{
		//printf("LEFT\n");
		if (mlx->pj.dir.x > 0.0000000000)
			mlx->pj.pos.y -= mlx->pj.dir.y - 0.1;
		else if (mlx->pj.dir.x < 0.0000000000)
			mlx->pj.pos.y -= mlx->pj.dir.y + 0.1;
		else if (mlx->pj.dir.y > 0.0000000000)
			mlx->pj.pos.x -= mlx->pj.dir.x - 0.1;
		else if (mlx->pj.dir.y < 0.0000000000)
			mlx->pj.pos.x -= mlx->pj.dir.x + 0.1;
	}
	return (EXIT_SUCCESS);
}

void	mlx_routine(t_mlx *mlx)
{
	mlx_loop_hook(mlx->mlx, print_all, mlx);
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
	printf("dir-[%f][%f]\n", mlx->pj.dir.y, mlx->pj.dir.x);
	mlx->map[(int)mlx->pj.pos.y][(int)mlx->pj.pos.x] = '0';
	mlx->img.pxl_unit = get_map_pxl_unit(mlx);
	mlx_routine(mlx);
	return (0);
}

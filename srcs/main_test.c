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

int	print_all(t_mlx *mlx)
{
	int		row;
	int		col;
	int		x;
	int		y;
	char	*tmp;
	t_color	color;

	row = 0;
	y = 0;
	while (mlx->map[row] != NULL)
	{
		x = 0;
		col = 0;
		while (mlx->map[row][col] != '\0')
		{
			if (mlx->map[row][col] == '0')
				color = make_color(255, 255, 255, 255);
			else if (mlx->map[row][col] == '1')
				color = make_color(255, 0, 74, 247);
			else
				color = make_color(255, 255, 0, 242);
			tmp = mlx->img.addr + ((y * mlx->img.line_len) + x);
			*(unsigned int *)tmp = color.code;
			x += 4;
			++col;
		}
		++y;
		++row;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	return (EXIT_SUCCESS);
}

void	mlx_routine(t_mlx *mlx)
{
	mlx_loop_hook(mlx->mlx, print_all, mlx);
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
	mlx_routine(mlx);
	ft_free_tab((void **)map);
	return (0);
}

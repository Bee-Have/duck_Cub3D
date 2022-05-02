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
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bits_pxl
									, &mlx->img.line_len
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

int	key_hook(int keycode, t_mlx *mlx)
{
	if (keycode == 65307)
		mlx_destroy_window(mlx->mlx, mlx->win);
	return (EXIT_SUCCESS);
}

void	draw_square(t_mlx *mlx, int size)
{
	char	*tmp;
	t_color	color;
	int		y;
	int		x;

	color = make_color(255, 255, 255, 255);
	y = 0;
	while (y < size * 4)
	{
		x = 0;
		while (x < size * 4)
		{
			tmp = mlx->img.addr + ((y * 1920) + x);
			*(unsigned int *)tmp = color.code;
			x += 4;
		}
		y += 4;
	}
}

int	testing(t_mlx *mlx)
{
	draw_square(mlx, 200);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	return (EXIT_SUCCESS);
}

void	mlx_routine(t_mlx *mlx)
{
	mlx_loop_hook(mlx->mlx, testing, mlx);
	mlx_hook(mlx->win, 2, 1, key_hook, mlx);
	mlx_loop(mlx->mlx);
}

int	main(void)
{
	t_mlx	*mlx;

	mlx = init_mlx(1920, 1080);
	mlx_routine(mlx);
	return (EXIT_SUCCESS);
}

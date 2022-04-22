#include "cub3d.h"

int	print_all(t_mlx *mlx)
{
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img.img, 0, 0);
	return (EXIT_SUCCESS);
}

void	mlx_routine(t_mlx *mlx)
{
	mlx_loop_hook(mlx->mlx, print_all, mlx);
	mlx_loop(mlx->mlx);
}

void	init_window(char **map)
{
	t_mlx	mlx;

	mlx.mlx = mlx_init();
	mlx.mlx_win = mlx_new_window(mlx.mlx, 1920, 1080, "cub3D");
	mlx.img.img = mlx_new_image(mlx.mlx, 1920, 1080);
	mlx.img.addr = (int *)mlx_get_data_addr(&mlx.img.img, &mlx.img.bits_per_pxl
								, &mlx.img.line_length, &mlx.img.endian);
	mlx.map = map;
	mlx_routine(&mlx);
}

int	main(int ac, char **av)
{
	char	**map;

	if (ac < 2)
		return (EXIT_FAILURE);
	ft_get_file(av[1], &map);
	ft_print_tab(map);
	init_window(map);
	ft_freetab(map);
	return (EXIT_SUCCESS);
}

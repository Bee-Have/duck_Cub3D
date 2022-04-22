#include "cub3d.h"

int	main(int ac, char **av)
{
	char	**map;

	if (ac < 2)
		return (EXIT_FAILURE);
	//read map
	ft_get_file(av[1], &map);
	//print map
	ft_print_tab(map);
	ft_freetab(map);
	return (EXIT_SUCCESS);
}

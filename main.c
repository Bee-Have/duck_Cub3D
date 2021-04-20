
#include "cub3D.h"

int		main(int ac, char **av)
{
	if (ac == 0 || av[1][0] == '\0')
		return(0);
	get_infos(av[1]);
	return (0);
}

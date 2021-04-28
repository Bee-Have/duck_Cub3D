
#include "include/cub3D.h"

void	print_map(char **map)
{
	int		row;
	
	row = 0;
	while (map[row] != NULL)
	{
		printf("[%s]\n", map[row]);
		row++;
	}
	return ;
}
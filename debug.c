
#include "include/cub3D.h"

void	print_map(char **map)
{
	int		row;
	int		max_line;
	int		i;
	char	*supplement;

	row = 0;
	max_line = 0;
	i = 0;
	supplement = (char *)malloc(sizeof(char));
	if (!supplement)
		return ;
	while (map[row] != NULL)
	{
		while (map[row][i] != '\0')
			i++;
		if (max_line < i)
			max_line = i;
		i = 0;
		row++;
	}
	row = 0;
	while (map[row] != NULL)
	{
		supplement[0] = '\0';
		printf("[%s", map[row]);
		i = ft_strlen(map[row]);
		while (i < max_line)
		{
			supplement = ft_strjoin(supplement, " ");
			i++;
		}
		printf("%s]\n", supplement);
		supplement = strtrim(supplement, 1, 0);
		row++;
	}
}
#include "../include/ft_ls.h"

int	parse_options(int argc, char **argv, t_options *options)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc && argv[i][0] == '-' && argv[i][1] != '\0')
	{
		j = 1;
		while (argv[i][j])
		{
			if (argv[i][j] == 'l')
				options->l = 1;
			else if (argv[i][j] == 'R')
				options->R = 1;
			else if (argv[i][j] == 'a')
				options->a = 1;
			else if (argv[i][j] == 'r')
				options->r = 1;
			else if (argv[i][j] == 't')
				options->t = 1;
			else
			{
				write(2, "ft_ls: invalid option -- '", 27);
				write(2, &argv[i][j], 1);
				write(2, "'\n", 2);
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (i);
}

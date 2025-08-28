#include "../include/ft_ls.h"

int	main(int argc, char **argv)
{
	t_options	options;
	int			i;
	int			file_count;

	/* Initialize options to 0 */
	options.l = 0;
	options.R = 0;
	options.a = 0;
	options.r = 0;
	options.t = 0;

	/* Parse command line options */
	i = parse_options(argc, argv, &options);
	if (i == -1)
	{
		print_usage();
		return (1);
	}

	/* Count remaining arguments (files/directories) */
	file_count = argc - i;

	/* If no files specified, use current directory */
	if (file_count == 0)
	{
		return (ft_ls(".", &options));
	}

	/* Process each specified file/directory */
	while (i < argc)
	{
		if (ft_ls(argv[i], &options) != 0)
			return (1);
		i++;
	}

	return (0);
}

void	print_usage(void)
{
	write(2, "Usage: ft_ls [-alRrt] [file ...]\n", 33);
}

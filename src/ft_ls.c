#include "../include/ft_ls.h"

int	ft_ls(char *path, t_options *options)
{
	DIR				*dir;
	struct dirent	*entry;
	struct stat		file_stat;

	/* Try to open as directory first */
	dir = opendir(path);
	if (dir == NULL)
	{
		/* If it's not a directory, check if it's a file */
		if (stat(path, &file_stat) == 0)
		{
			/* It's a file, just print its name */
			write(1, path, ft_strlen(path));
			write(1, "\n", 1);
			return (0);
		}
		else
		{
			/* File/directory doesn't exist */
			perror(path);
			return (1);
		}
	}

	/* Read directory entries */
	while ((entry = readdir(dir)) != NULL)
	{
		/* Skip hidden files unless -a option is specified */
		if (!options->a && entry->d_name[0] == '.')
			continue;

		/* Print file name */
		write(1, entry->d_name, ft_strlen(entry->d_name));
		write(1, "\n", 1);
	}

	closedir(dir);
	return (0);
}

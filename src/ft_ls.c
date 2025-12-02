#include "../include/ft_ls.h"

t_file	*create_file_node(char *name, char *dir_path)
{
	t_file	*node;
	char	*full_path;
	char	*temp;

	node = ft_malloc(sizeof(t_file));
	node->name = ft_strdup(name);
	if (ft_strcmp(dir_path, ".") == 0)
		full_path = ft_strdup(name);
	else
	{
		temp = ft_strjoin(dir_path, "/");
		full_path = ft_strjoin(temp, name);
		ft_free(temp);
	}
	node->path = full_path;
	if (lstat(full_path, &node->stat) != 0)
	{
		perror(full_path);
		node->stat.st_mtime = 0;
	}
	node->next = NULL;
	return (node);
}

void	add_file_node(t_file **head, t_file *new_node)
{
	t_file	*current;

	if (!*head)
	{
		*head = new_node;
		return;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

void	free_file_list(t_file *head)
{
	t_file	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		ft_free(temp->name);
		ft_free(temp->path);
		ft_free(temp);
	}
}

static void	swap_nodes(t_file *a, t_file *b)
{
	char		*temp_name;
	char		*temp_path;
	struct stat	temp_stat;

	temp_name = a->name;
	temp_path = a->path;
	temp_stat = a->stat;
	a->name = b->name;
	a->path = b->path;
	a->stat = b->stat;
	b->name = temp_name;
	b->path = temp_path;
	b->stat = temp_stat;
}

void	sort_file_list(t_file **head, t_options *options)
{
	t_file	*i;
	t_file	*j;
	int		swap;

	if (!*head)
		return;
	i = *head;
	while (i)
	{
		j = i->next;
		while (j)
		{
			swap = 0;
			if (options->t)
				swap = (i->stat.st_mtime < j->stat.st_mtime);
			else
				swap = (ft_strcmp(i->name, j->name) > 0);
			if (options->r)
				swap = !swap;
			if (swap)
				swap_nodes(i, j);
			j = j->next;
		}
		i = i->next;
	}
}

void	print_permissions(mode_t mode)
{
	ft_putchar((S_ISDIR(mode)) ? 'd' : '-');
	ft_putchar((mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((mode & S_IWUSR) ? 'w' : '-');
	ft_putchar((mode & S_IXUSR) ? 'x' : '-');
	ft_putchar((mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((mode & S_IWGRP) ? 'w' : '-');
	ft_putchar((mode & S_IXGRP) ? 'x' : '-');
	ft_putchar((mode & S_IROTH) ? 'r' : '-');
	ft_putchar((mode & S_IWOTH) ? 'w' : '-');
	ft_putchar((mode & S_IXOTH) ? 'x' : '-');
}

void	print_long_format(t_file *file)
{
	struct passwd	*pwd;
	struct group	*grp;
	char			*time_str;
	int				i;

	print_permissions(file->stat.st_mode);
	ft_putstr("  ");
	ft_putnbr(file->stat.st_nlink);
	ft_putchar(' ');
	pwd = getpwuid(file->stat.st_uid);
	ft_putstr(pwd ? pwd->pw_name : "unknown");
	ft_putstr("  ");
	grp = getgrgid(file->stat.st_gid);
	ft_putstr(grp ? grp->gr_name : "unknown");
	ft_putchar(' ');
	ft_putnbr(file->stat.st_size);
	ft_putchar(' ');
	time_str = ctime(&file->stat.st_mtime);
	i = 4;
	while (i < 16)
	{
		ft_putchar(time_str[i]);
		i++;
	}
	ft_putchar(' ');
	ft_putstr(file->name);
	ft_putchar('\n');
}

void	print_file_list(t_file *head, t_options *options)
{
	while (head)
	{
		if (options->l)
			print_long_format(head);
		else
		{
			write(1, head->name, ft_strlen(head->name));
			write(1, "\n", 1);
		}
		head = head->next;
	}
}

static int	is_dot_or_dotdot(const char *name)
{
	if (name[0] == '.')
	{
		if (name[1] == '\0')
			return (1);
		if (name[1] == '.' && name[2] == '\0')
			return (1);
	}
	return (0);
}

static void	process_recursive(t_file *file_list, t_options *options)
{
	t_file	*current;

	current = file_list;
	while (current)
	{
		if (S_ISDIR(current->stat.st_mode) && 
			!is_dot_or_dotdot(current->name))
		{
			ft_putchar('\n');
			ft_putstr(current->path);
			ft_putstr(":\n");
			ft_ls_recursive(current->path, options, 0);
		}
		current = current->next;
	}
}

int	ft_ls_recursive(char *path, t_options *options, int print_header)
{
	DIR				*dir;
	struct dirent	*entry;
	t_file			*file_list;
	t_file			*new_node;

	file_list = NULL;
	dir = opendir(path);
	if (dir == NULL)
	{
		perror(path);
		return (1);
	}
	if (print_header && options->R)
	{
		ft_putstr(path);
		ft_putstr(":\n");
	}
	while ((entry = readdir(dir)) != NULL)
	{
		if (!options->a && entry->d_name[0] == '.')
			continue;
		new_node = create_file_node(entry->d_name, path);
		add_file_node(&file_list, new_node);
	}
	closedir(dir);
	sort_file_list(&file_list, options);
	print_file_list(file_list, options);
	if (options->R)
		process_recursive(file_list, options);
	free_file_list(file_list);
	return (0);
}

int	ft_ls(char *path, t_options *options)
{
	return (ft_ls_recursive(path, options, 1));
}

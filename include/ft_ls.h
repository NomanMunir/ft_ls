#ifndef FT_LS_H
# define FT_LS_H

# define _DEFAULT_SOURCE
# define _BSD_SOURCE
# define _XOPEN_SOURCE 700

# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <errno.h>

/* Structure to hold command line options */
typedef struct s_options
{
	int	l;		/* -l: long format */
	int	R;		/* -R: recursive */
	int	a;		/* -a: show hidden files */
	int	r;		/* -r: reverse order */
	int	t;		/* -t: sort by time */
}	t_options;

/* Structure to hold file information */
typedef struct s_file
{
	char			*name;
	char			*path;
	struct stat		stat;
	struct s_file	*next;
}	t_file;

/* Function prototypes */
int		main(int argc, char **argv);
int		parse_options(int argc, char **argv, t_options *options);
void	print_usage(void);
int		ft_ls(char *path, t_options *options);
int		ft_ls_recursive(char *path, t_options *options, int print_header);

/* File list management */
t_file	*create_file_node(char *name, char *dir_path);
void	add_file_node(t_file **head, t_file *new_node);
void	free_file_list(t_file *head);
void	sort_file_list(t_file **head, t_options *options);
void	print_file_list(t_file *head, t_options *options);

/* Utility functions */
void	*ft_malloc(size_t size);
void	ft_free(void *ptr);
char	*ft_strdup(const char *s);
int		ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strjoin(const char *s1, const char *s2);
void	ft_putstr(const char *s);
void	ft_putchar(char c);
void	ft_putnbr(long n);
int		ft_numlen(long n);

/* Long format helpers */
void	print_permissions(mode_t mode);
void	print_long_format(t_file *file);

#endif

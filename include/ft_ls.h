#ifndef FT_LS_H
# define FT_LS_H

# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
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

/* Utility functions */
void	*ft_malloc(size_t size);
void	ft_free(void *ptr);
char	*ft_strdup(const char *s);
int		ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);

#endif

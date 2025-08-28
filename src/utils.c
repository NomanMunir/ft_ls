#include "../include/ft_ls.h"

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		perror("malloc");
		exit(1);
	}
	return (ptr);
}

void	ft_free(void *ptr)
{
	if (ptr)
		free(ptr);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	int		len;
	int		i;

	if (!s)
		return (NULL);
	
	len = ft_strlen(s);
	dup = ft_malloc(len + 1);
	
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	
	return (dup);
}

int	ft_strlen(const char *s)
{
	int	len;

	if (!s)
		return (0);
	
	len = 0;
	while (s[len])
		len++;
	
	return (len);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (0);
	
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

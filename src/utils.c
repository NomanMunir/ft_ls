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

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*result;
	int		len1;
	int		len2;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = ft_malloc(len1 + len2 + 1);
	i = 0;
	while (i < len1)
	{
		result[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < len2)
	{
		result[i + j] = s2[j];
		j++;
	}
	result[i + j] = '\0';
	return (result);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(const char *s)
{
	if (s)
		write(1, s, ft_strlen(s));
}

int	ft_numlen(long n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

void	ft_putnbr(long n)
{
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
	}
	if (n >= 10)
		ft_putnbr(n / 10);
	ft_putchar((n % 10) + '0');
}

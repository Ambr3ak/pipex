#include "../inc/pipex.h"

int	ft_strcmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*str1;
	unsigned char	*str2;
	size_t size;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	size = ft_strlen(s1);
	i = 0;
	if (size != n)
		return (1);
	while (i < n && str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	if (i < n)
		return (str1[i] - str2[i]);
	else
		return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (!n)
		return (0);
	i = 0;
	while (i < n && str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	if (i < n)
		return (str1[i] - str2[i]);
	else
		return (0);
}
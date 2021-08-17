/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 10:29:00 by abourdar          #+#    #+#             */
/*   Updated: 2021/06/30 12:41:03 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

char	*ft_strdup_long(t_glb *glb, const char *s1, int size)
{
	int		i;
	char	*dest;

	i = 0;
	dest = malloc_list(glb, (size + 1) * sizeof(char));
	if (!(dest))
		return (0);
	while (s1[i])
	{
		dest[i] = s1[i];
		if (dest[i] == ' ')
			dest[i] = '3';
		i++;
	}
	while (i < size)
	{
		dest[i] = '3';
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(t_glb *glb, const char *s1)
{
	int		i;
	int		size;
	char	*dest;

	i = 0;
	size = ft_strlen(s1);
	dest = malloc_list(glb, (size + 1) * sizeof(char));
	if (!(dest))
		return (0);
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

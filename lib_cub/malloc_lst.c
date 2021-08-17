/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 10:38:12 by abourdar          #+#    #+#             */
/*   Updated: 2021/07/19 10:38:15 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	*lst_add(t_glb *glb, void *ptr)
{
	t_list	*elem;

	elem = ft_lstnew(ptr);
	if (!(elem))
	{
		free(ptr);
		return (NULL);
	}
	if (!(glb->ptrs))
		glb->ptrs = elem;
	else
		ft_lstadd_back(&glb->ptrs, elem);
	return (ptr);
}

void	*malloc_list(t_glb *glb, int size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	if (!lst_add(glb, ptr))
	{
		free(ptr);
		return (NULL);
	}
	return (ptr);
}

void	*free_malloc_lst(t_glb *glb)
{
	ft_lstclear(&glb->ptrs, free);
	return (0);
}

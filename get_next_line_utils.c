/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 10:47:58 by angomes-          #+#    #+#             */
/*   Updated: 2023/06/08 15:15:00 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	node->content = content;
	node->count = 0;
	node->next = NULL;
	return (node);
}

// void	ft_lstadd_back(t_list **lst, t_list *new)
// {
// 	t_list	*last;
//
// 	if (!new)
// 		return ;
// 	if (!last)
// 		*lst = new;
// 	else
// 	{
// 		last->next = new;
// 	}
// }

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;
	size_t	total_size;
	size_t	i;

	i = 0;
	total_size = nmemb * size;
	if (total_size != 0 && total_size / size != nmemb)
		return (NULL);
	ptr = (void *)malloc(total_size);
	if (!ptr)
		return (NULL);
	while (i < total_size)
	{
		ptr[i] = '\0';
		i++;
	}
	return (ptr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_teste.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 10:47:58 by angomes-          #+#    #+#             */
/*   Updated: 2023/06/11 18:07:40 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <threads.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = calloc(sizeof(t_list), sizeof(t_list));
	if (node == NULL)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

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

int	ft_lstsize(t_list *lst)
{
	int	count;
  int iterator;

  iterator = 0;
	count = 0;
	while (lst)
	{
    iterator = 0;
		while (lst->content[iterator])
		{
			count++;
      iterator++;
		}
    lst = lst -> next;
	}
	return (count);
}

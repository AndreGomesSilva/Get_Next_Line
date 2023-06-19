/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 10:47:58 by angomes-          #+#    #+#             */
/*   Updated: 2023/06/19 15:20:37 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = (t_list *)ft_calloc(1, sizeof(t_list));
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
	ptr = (char *)malloc(total_size);
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
	int	iterator;

	iterator = 0;
	count = 0;
	while (lst && lst->content)
	{
		iterator = 0;
		while (lst->content[iterator] && lst->content)
		{
			count++;
			iterator++;
		}
		lst = lst->next;
	}
	return (count);
}

void	ft_lstclear(t_list **lst)
{
	t_list	*temp_node;
	t_list	*next;

	if (!lst)
		return ;
	temp_node = *lst;
	while (temp_node != NULL)
	{
		next = temp_node->next;
		free(temp_node->content);
		free(temp_node);
		temp_node = next;
	}
	*lst = NULL;
}

int	ft_strlen(char *content)
{
	int	count;

	count = 0;
	while (*content)
	{
		content++;
		count++;
	}
	return (count);
}

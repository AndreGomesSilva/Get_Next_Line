/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 10:42:50 by angomes-          #+#    #+#             */
/*   Updated: 2023/06/12 19:59:59 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

int		ft_read(int fd, void *buffer, size_t BUFFER);
int		ft_check_end_line(t_list *lst, size_t len);
char	*ft_split_line(char *content, t_list **rest_node, size_t len);
char	*return_str(t_list *lst);

char	*get_next_line(int fd)
{
	char			*buffer;
	t_list			*lst_line;
	static t_list	*rest_node;
	t_list			*first_node;
	int				check;
	int				b_read;

	buffer = NULL;
	if (rest_node)
	{
		check = ft_check_end_line(rest_node, BUFFER_SIZE);
		if (check > 0)
		{
			first_node = ft_lstnew(ft_split_line(rest_node->content, &rest_node,
						check));
		}
		if (check == 0)
		{
			buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
			if (!buffer)
				return (NULL);
			b_read = ft_read(fd, buffer, BUFFER_SIZE);
			if (b_read == 0 || b_read == -1)
			{
				free(buffer);
				return (NULL);
			}
			lst_line = ft_lstnew(buffer);
			first_node = ft_lstnew(rest_node->content);
			first_node->next = lst_line;
			check = ft_check_end_line(lst_line, BUFFER_SIZE);
			while (check == 0)
			{
				buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
				b_read = ft_read(fd, buffer, BUFFER_SIZE);
				if (b_read == 0 || b_read == -1)
				{
					free(buffer);
					return (NULL);
				}
				lst_line->next = ft_lstnew(buffer);
				if (lst_line->next != NULL)
					lst_line = lst_line->next;
				check = ft_check_end_line(lst_line, BUFFER_SIZE);
			}
			if (check > 0)
			{
				lst_line->content = ft_split_line(lst_line->content,
													&rest_node,
													check);
			}
		}
		buffer = return_str(first_node);
		ft_lstclear(&first_node);
		return (buffer);
	}
	else
	{
		buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!buffer)
			return (NULL);
		b_read = ft_read(fd, buffer, BUFFER_SIZE);
		if (b_read == 0 || b_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		lst_line = ft_lstnew(buffer);
		first_node = lst_line;
		check = ft_check_end_line(first_node, BUFFER_SIZE);
		while (check == 0)
		{
			buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
      if(!buffer)
        return(NULL);
			b_read = ft_read(fd, buffer, BUFFER_SIZE);
			if (b_read == 0 || b_read == -1)
			{
				free(buffer);
				return (NULL);
			}
			lst_line->next = ft_lstnew(buffer);
			if (lst_line->next != NULL)
				lst_line = lst_line->next;
			check = ft_check_end_line(lst_line, BUFFER_SIZE);
		}
		if (check > 0)
		{
			lst_line->content = ft_split_line(lst_line->content, &rest_node,
					check);
		}
		buffer = return_str(first_node);
		ft_lstclear(&first_node);
    		return (buffer);
	}
	ft_lstclear(&rest_node);
	return (NULL);
}

char	*return_str(t_list *lst)
{
	char	*str;
	int		iterator;
	int		size;
	t_list	head;
	int		second_iterator;

	iterator = 0;
	head = *lst;
	size = ft_lstsize(lst);
	str = (char *)ft_calloc(size + 1, sizeof(char));
	while (lst)
	{
		second_iterator = 0;
		while (size && lst->content[second_iterator])
		{
			str[iterator] = lst->content[second_iterator];
			iterator++;
			second_iterator++;
			size--;
		}
		lst = lst->next;
	}
	return (str);
}

char	*ft_split_line(char *content, t_list **rest_node, size_t len)
{
	char	*rest_of_content;
	char	*clear_content;
	char	*start_content;
	int		iterator;
	char	*rest_result;


	free(*rest_node);
	start_content = content;
	rest_of_content = &start_content[len];
	iterator = 0;
	while (rest_of_content[iterator])
		iterator++;
	rest_result = (char *)ft_calloc(iterator + 1, sizeof(char));
  if (!rest_result)
    return (NULL);
	while (iterator--)
	{
		rest_result[iterator] = rest_of_content[iterator];
	}
	*rest_node = ft_lstnew(rest_result);
	clear_content = (char *)ft_calloc(len + 1, sizeof(char));
	if (!clear_content)
		return (NULL);
	while (len--)
	{
		clear_content[len] = start_content[len];
	}
	free(start_content);
	return (clear_content);
}

int	ft_check_end_line(t_list *lst, size_t len)
{
	int	check;
	int	iterator;

	check = 0;
	iterator = 0;
	while (len--)
	{
		if (lst->content[iterator] == '\n' || lst-> content[iterator + 1] == '\0')
			return (check + iterator + 1);
		iterator++;
	}
	return (check);
}

int	ft_read(int fd, void *buffer, size_t BUFFER)
{
	int	bytes_read;

	bytes_read = read(fd, buffer, BUFFER);
	if (bytes_read == 0 || bytes_read == -1)
		return (0);
	return (bytes_read);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*text;
//
// 	fd = open("test.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		printf("failed to open the file");
// 		return (1);
// 	}
// 	text = get_next_line(fd);
// 	printf("%s\n", text);
// 	free(text);
// 	text = get_next_line(fd);
// 	printf("%s\n", text);
// 	free(text);
// }

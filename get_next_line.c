/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 10:42:50 by angomes-          #+#    #+#             */
/*   Updated: 2023/06/20 16:58:21 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_split_line(char *content, t_list **rest_node, size_t len);
static char	*look_for_line(t_list **rest_node, int fd);
static char	*return_str(t_list *lst);
static int	make_first_node(t_list **first_node, int fd, t_list **lst_node);

char	*get_next_line(int fd)
{
	char			*result;
	static t_list	*rest_node;
	int				check;
	t_list			*first_node;

	result = NULL;
	if (rest_node)
	{
		check = ft_check_end_line(rest_node, 0, rest_node);
		if (check > 0 && ft_lstsize(rest_node) != check)
		{
			result = ft_split_line(return_str(rest_node), &rest_node, check);
		}
		else if (rest_node->content[0] != 0)
		{
			first_node = ft_lstnew(return_str(rest_node));
			ft_lstclear(&rest_node);
			first_node->next = ft_lstnew(look_for_line(&rest_node, fd));
			result = return_str(first_node);
			ft_lstclear(&first_node);
		}
	}
	else
		result = look_for_line(&rest_node, fd);
	return (result);
}

static char	*look_for_line(t_list **rest_node, int fd)
{
	char	*buffer;
	t_list	*first_node;
	int		b_read;
	int		check;
	t_list	*lst_node;

	b_read = make_first_node(&first_node, fd, &lst_node);
	if (!b_read)
		return (NULL);
	check = ft_check_end_line(first_node, b_read, first_node);
	while (check == 0)
	{
		buffer = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!buffer)
			return (NULL);
		b_read = read(fd, buffer, BUFFER_SIZE);
		lst_node->next = ft_lstnew(buffer);
		lst_node = lst_node->next;
		check = ft_check_end_line(lst_node, b_read, first_node);
	}
	if (check > 0 && ft_lstsize(lst_node) != check && b_read > 0)
		lst_node->content = ft_split_line(lst_node->content, rest_node, check);
	buffer = return_str(first_node);
	ft_lstclear(&first_node);
	return (buffer);
}

static int	make_first_node(t_list **first_node, int fd, t_list **lst_node)
{
	char	*buffer;
	int		b_read;

	b_read = 1;
	buffer = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (0);
	b_read = read(fd, buffer, BUFFER_SIZE);
	if (b_read == 0 || b_read == -1)
	{
		free(buffer);
		return (0);
	}
	*lst_node = ft_lstnew(buffer);
	*first_node = *lst_node;
	return (b_read);
}

static char	*return_str(t_list *lst)
{
	char	*str;
	int		iterator;
	int		size;
	int		second_iterator;

	iterator = 0;
	size = ft_lstsize(lst);
	str = (char *)ft_calloc(size + 1, sizeof(char));
	if (!str)
		return (NULL);
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

static char	*ft_split_line(char *content, t_list **rest_node, size_t len)
{
	char	*rest_of_content;
	char	*clear_content;
	int		iterator;
	char	*rest_result;

	rest_of_content = &content[len];
	iterator = 0;
	while (rest_of_content[iterator])
		iterator++;
	clear_content = (char *)ft_calloc(len + 1, sizeof(char));
	if (!clear_content)
		return (NULL);
	while (len--)
		clear_content[len] = content[len];
	rest_result = (char *)ft_calloc(iterator + 1, sizeof(char));
	if (!rest_result)
		return (NULL);
	while (iterator--)
		rest_result[iterator] = rest_of_content[iterator];
	if (*rest_node)
		ft_lstclear(rest_node);
	*rest_node = ft_lstnew(rest_result);
	free(content);
	return (clear_content);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*text;
//
// 	fd = open("41_with_nl", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		printf("failed to open the file");
// 		return (1);
// 	}
// 	text = get_next_line(fd);
// 	// while (text)
// 	// {
// 	// 	free(text);
// 	// 	text = get_next_line(fd);
// 	// }
// 	printf("%s", text);
// 	free(text);
// 	text = get_next_line(fd);
// 	printf("%s", text);
// 	free(text);
// 	text = get_next_line(fd);
// 	printf("%s", text);
// 	free(text);
// 	// text = get_next_line(fd);
// 	// printf("%s", text);
// 	// free(text);
// 	// text = get_next_line(fd);
// 	// printf("%s", text);
// 	// free(text);
// 	// text = get_next_line(fd);
// 	// printf("%s", text);
// 	// free(text);
// 	close(fd);
// 	return (0);
// }

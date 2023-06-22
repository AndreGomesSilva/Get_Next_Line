/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:48:15 by angomes-          #+#    #+#             */
/*   Updated: 2023/06/22 19:40:17 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

char				*get_next_line(int fd);
t_list				*ft_lstnew(void *content);
void				*ft_calloc(size_t nmemb, size_t size);
int					ft_lstsize(t_list *lst);
void				ft_lstclear(t_list **lst);
int					ft_check_end_line(t_list *lst, int bytes_read,
						t_list *rest_node);

#endif

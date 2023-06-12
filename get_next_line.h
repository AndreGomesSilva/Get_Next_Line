#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

char				*get_next_line(int fd);
t_list				*ft_lstnew(void *content);
t_list				*ft_lstadd_back(t_list *lst, t_list *new);
void				*ft_calloc(size_t nmemb, size_t size);
t_list				*ft_lstlast(t_list *lst);
int					ft_lstsize(t_list *lst);
void				ft_lstclear(t_list **lst);

#endif

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# define BUFFER_SIZE 50

typedef struct s_list
{
	char			*content;
	int				count;
	struct s_list	*next;
}					t_list;

char				*get_next_line(int fd);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				*ft_calloc(size_t nmemb, size_t size);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenasurovtseva <elenasurovtseva@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 03:20:09 by elsurovt          #+#    #+#             */
/*   Updated: 2024/07/29 23:10:48 by elenasurovt      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

//------------LIBFT---------------/
// Mandatory Part 1:
int		ft_isalpha(int a);
int		ft_isdigit(int a);
int		ft_isalnum(int c);
int		ft_isascii(int a);
int		ft_isprint(int a);
int		ft_toupper(int a);
int		ft_tolower(int c);
int		ft_atoi(const char *str);
int		ft_memcmp(const void *str1, const void *str2, size_t a);
int		ft_strncmp(const char *s1, const char *s2, size_t a);
char	*ft_strdup(const char *s);
char	*ft_strchr(const char *str, int c);
char	*ft_strrchr(const char *str, int a);
char	*ft_strnstr(const char *big, const char *little, size_t len);
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t siz);
void	ft_bzero(void *s, size_t a);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
void 	*ft_calloc(size_t count, size_t size);
void 	*ft_memset(void *str, int a, size_t len);
void	*ft_memchr(const void *str, int a, size_t b);
void	*ft_memcpy(void *dst, const void *src, size_t a);
void	*ft_memmove(void *dst, const void *src, size_t a);
// Mandatory Part 2:
char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char 	*ft_strtrim(char const *s1, char const *set);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
//Part Bonus:
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

static int	ft_wordcount(char const *s, char c);
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));


//------------GET_NEXT_LINE---------------/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# ifndef MAX_F_OPENED
#  define MAX_F_OPENED 1024
# endif

char	*get_next_line(int fd);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:52:22 by moabed            #+#    #+#             */
/*   Updated: 2025/08/19 21:55:06 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlen(const char *str);
void		*ft_memchr(const void *s, int c, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
void		*ft_memset(void *s, int c, size_t n);
void		ft_putnbr_fd(int nb, int fd);
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putstr_fd(char *s, int fd);
int			ft_atoi(const char *nptr);
int			ft_tolower(int x);
int			ft_toupper(int x);
int			ft_isalnum(int x);
int			ft_isalpha(int x);
int			ft_isascii(int x);
int			ft_isdigit(int x);
int			ft_isprint(int x);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
int			ft_strncmp(char *s1, char *s2, unsigned int n);
char		**ft_split(char const *s, char c);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strrchr(const char *s, int c);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *src);
char		*ft_itoa(int n);
char		*ft_strnstr(const char *big, const char *little, size_t len);
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;
void		ft_lstadd_front(t_list **lst, t_list *new);
t_list		*ft_lstnew(void *content);
t_list		*ft_lstlast(t_list *lst);
int			ft_lstsize(t_list *lst);
#endif

// struct s_list *next; cus next pointer points to an address of type struct
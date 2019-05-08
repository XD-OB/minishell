/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 01:07:21 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/03 02:41:12 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include "ft_printf.h"
# define BUFF_SIZE 1000

typedef struct		s_gnl
{
	int				fd;
	char			*content;
	struct s_gnl	*next;
}					t_gnl;

typedef struct		s_mult
{
	int				i;
	int				j;
	int				n1;
	int				n2;
	int				i_n1;
	int				i_n2;
	int				carry;
	int				sum;
	int				*result;
	char			*s;
}					t_mult;

typedef struct		s_bt
{
	void			*item;
	struct s_bt		*left;
	struct s_bt		*right;
}					t_bt;

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

/*
** BTREE Functions
*/

t_bt				*bt_create_node(void *item);
void				bt_insert_item(t_bt **root, void *item,
		int (*cmpf)(void *, void *));
t_bt				*bt_search_item(t_bt *root, void *data_ref,
		int (*cmpf)(void *, void *));
void				bt_apply_infix(t_bt *root, void (*applyf)(void *));
void				bt_apply_revinfix(t_bt *root, void (*applyf)(void *));
void				bt_apply_prefix(t_bt *root, void (*applyf)(void *));
void				bt_apply_suffix(t_bt *root, void (*applyf)(void *));
int					bt_size_count(t_bt *root);
int					bt_level_count(t_bt *root);
void				bt_free(t_bt **root, void (*freef)(void **));

int					get_next_line(const int fd, char **line);
void				ft_printhex(int n);
int					ft_intlen(int n);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(long long int n);
char				*ft_ltoa(long int n);
char				*ft_lltoa(long long int n);
char				*ft_itoa_base(long long int val, int base);
char				*ft_ulltoa_base(unsigned long long val, int base);
char				*ft_utoa(size_t n);
char				*ft_ultoa(unsigned long int n);
char				*ft_ulltoa(unsigned long long int n);
char				*ft_utoa_base(size_t val, int base);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
size_t				ft_strlen(const char *str);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strncpy(char *dest, const char *src, size_t len);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strncat(char *dest, const char *src, size_t n);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
char				*ft_strstr(const char *str, const char *find);
char				*ft_strnstr(const char *str, const char *find, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strpbrk(const char *s1, const char *s2);
char				*ft_strdup(const char *src);
char				*ft_strndup(const char *src, int n);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void*, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
int					ft_sqrt(int nb);
int					ft_prime(int nb);
char				*ft_strlowcase(char *str);
char				*ft_strupcase(char *str);
void				ft_swap(int *a, int *b);
char				*ft_strrev(char *str);
int					ft_isblank(int c);
int					ft_isxdigit(int c);
char				*ft_strnjoin(char *s1, char *s2, size_t len);
int					ft_atoibase(char *str, char *base_from);
void				ft_strswap(char **s1, char **s2);
char				*ft_str_pushback(char *str, char c);
char				*ft_strsum(char *str1, char *str2, int base);
char				*ft_strcnew(size_t size, char c);
char				*ft_strmult(char *num1, char *num2, int base);
char				*ft_strpower(int base, int exponent, int x);
int					ft_max(int a, int b);
int					ft_min(int a, int b);
char				*ft_poslltoa(long long int n);

#endif

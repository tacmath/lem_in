/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   libft.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/02 13:14:48 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/13 11:08:50 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# ifndef BUFF_SIZE
#  define BUFF_SIZE 32
# endif
# include <string.h>
# include <stdint.h>
# include <wchar.h>
# include "ft_printf.h"

typedef struct			s_list
{
	void				*content;
	size_t				content_size;
	struct s_list		*next;
}						t_list;

int						get_next_line(const int fd, char **line);
void					*ft_memset(void *b, int c, size_t len);
void					ft_bzero(void *s, size_t n);
void					*ft_memcpy(void *dst, const void *src, size_t n);
void					*ft_memccpy(void *dst,
							const void *src, int c, size_t n);
void					*ft_memmove(void *dst, const void *src, size_t len);
void					*ft_memchr(const void *s, int c, size_t n);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
size_t					ft_strlen(const char *s);
char					*ft_strdup(const char *s1);
char					*ft_strcpy(char *dst, const char *src);
char					*ft_strncpy(char *dst, const char *src, size_t len);
char					*ft_strcat(char *s1, const char *s2);
char					*ft_strncat(char *s1, const char *s2, size_t n);
size_t					ft_strlcat(char *dst, const char *src, size_t size);
char					*ft_strstr(const char *haystack, const char *needle);
int						ft_strcmp(const char *s1, const char *s2);
int						ft_strncmp(const char *s1,
							const char *s2, size_t n);
int						ft_atoi(const char *str);
int						ft_isalpha(int c);
int						ft_isdigit(int c);
char					*ft_strnstr(const char *haystack,
							const char *needle, size_t len);
int						ft_toupper(int c);
int						ft_tolower(int c);
int						ft_isalnum(int c);
int						ft_isascii(int c);
int						ft_isprint(int c);
char					*ft_strchr(const char *s, int c);
char					*ft_strrchr(const char *s, int c);

void					*ft_memalloc(size_t size);
void					ft_memdel(void **ap);
char					*ft_strnew(size_t size);
void					ft_strdel(char **as);
void					ft_strclr(char *s);
void					ft_striter(char *s, void (*f)(char *));
void					ft_striteri(char *s, void (*f)(unsigned int, char *));
char					*ft_strmap(char const *s, char (*f)(char));
char					*ft_strmapi(char const *s,
								char (*f)(unsigned int, char));
int						ft_strequ(char const *s1, char const *s2);
int						ft_strnequ(char const *s1, char const *s2, size_t n);
char					*ft_strsub(char const *s,
							unsigned int start, size_t len);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_strtrim(char const *s);
char					**ft_strsplit(char const *s, char c);
void					ft_putchar(char c);
void					ft_putstr(char const *s);
void					ft_putendl(char const *s);
void					ft_putnbr(int n);
void					ft_putchar_fd(char c, int fd);
void					ft_putstr_fd(char const *s, int fd);
void					ft_putendl_fd(char const *s, int fd);
void					ft_putnbr_fd(int n, int fd);
char					*ft_itoa(int n);

t_list					*ft_lstnew(void const *content,
							size_t content_size);
void					ft_lstadd(t_list **alst, t_list *new);
void					ft_lstiter(t_list *lst, void (*f)(t_list *elem));
void					ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void					ft_lstdelone(t_list **alst,
							void (*del)(void *, size_t));
t_list					*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

void					*ft_realloc(void **in, size_t
							old_size, size_t new_size);
char					**ft_split_whitespaces(char *str);
int						ft_str_is_alpha(char *str);
int						ft_str_is_numeric(char *str);
void					ft_sort_integer_table(int *tab, int size);
void					ft_swap(void *a, void *b, size_t size);
int						ft_max(int a, int b);
int						ft_min(int a, int b);
int						ft_abs(int a);

int						ft_strchri(const char *s, int c);
int						ft_ischarset(char c, char *charset);
char					*ft_itoa_base(int value, int base);
char					*ft_uitoa_base(unsigned int value, int base);
char					*ft_luitoa_base(unsigned long int value, int base);
char					*ft_lluitoa_base(unsigned long long int value,
							int base);
char					*ft_juitoa_base(uintmax_t value, int base);
char					*ft_zuitoa_base(size_t value, int base);

char					*ft_uitoa_basem(unsigned int value, int base);
char					*ft_luitoa_basem(unsigned long int value, int base);
char					*ft_lluitoa_basem(unsigned long long int value,
							int base);
unsigned int			ft_compl(int a);
unsigned long int		ft_lcompl(long int a);
unsigned long long int	ft_llcompl(long long int a);
int64_t					ft_iterative_power(int nbr, int pow);
char					*ft_strjoin_free(char *s1, char *s2);

double					ft_dbl_truncate(double nbr);
double					ft_dbl_get_deci(double nbr);
unsigned char			*ft_handle_wchar(wchar_t *ws);
char					*ft_dtoa(double nbr, int prec);
char					*ft_dtoat(double nbr);
char					*ft_litoa(long int nbr);
char					*ft_llitoa(long long int nbr);
char					*ft_jitoa(intmax_t nbr);
char					*ft_zitoa(ssize_t nbr);
char					*ft_strtolower(char *s);
char					*ft_str_replace(char *s1, char *s2);
char					*ft_ldtoa(long double nbr, int prec);
char					*ft_ldtoat(long double nbr);
long double				ft_ldbl_truncate(long double nbr);
long double				ft_ldbl_get_deci(long double nbr);
char					*ft_strsub_free(char *s,
							unsigned int start, size_t len);

char					*ft_strjoin_mult(int n, ...);
int						ft_super_free(int n, ...);

#endif

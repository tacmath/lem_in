/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/23 15:41:03 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/08 14:39:48 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>

/*
** Some ANSI escape sequences
** https://misc.flogisoft.com/bash/tip_colors_and_formatting
*/

# define _BLACK_ "\e[30m"
# define _RED_ "\e[31m"
# define _GREEN_ "\e[32m"
# define _YELLOW_ "\e[33m"
# define _BLUE_ "\e[34m"
# define _MAGENTA_ "\e[35m"
# define _CYAN_ "\e[36m"
# define _WHITE_ "\e[37m"
# define _BRIGHT_BLACK_ "\e[90m"
# define _BRIGHT_RED_ "\e[91m"
# define _BRIGHT_GREEN_ "\e[92m"
# define _BRIGHT_YELLOW_ "\e[93m"
# define _BRIGHT_BLUE_ "\e[94m"
# define _BRIGHT_MAGENTA_ "\e[95m"
# define _BRIGHT_CYAN_ "\e[96m"
# define _BRIGHT_WHITE_ "\e[97m"
# define _EOC_ "\e[39m"

# define _BACK_BLACK_ "\e[40m"
# define _BACK_RED_ "\e[41m"
# define _BACK_GREEN_ "\e[42m"
# define _BACK_YELLOW_ "\e[43m"
# define _BACK_BLUE_ "\e[44m"
# define _BACK_MAGENTA_ "\e[45m"
# define _BACK_CYAN_ "\e[46m"
# define _BACK_WHITE_ "\e[47m"
# define _BACK_BRIGHT_BLACK_ "\e[100m"
# define _BACK_BRIGHT_RED_ "\e[101m"
# define _BACK_BRIGHT_GREEN_ "\e[102m"
# define _BACK_BRIGHT_YELLOW_ "\e[103m"
# define _BACK_BRIGHT_BLUE_ "\e[104m"
# define _BACK_BRIGHT_MAGENTA_ "\e[105m"
# define _BACK_BRIGHT_CYAN_ "\e[106m"
# define _BACK_BRIGHT_WHITE_ "\e[107m"
# define _EOBC_ "\e[49m"

# define _BOLD_ "\e[1m"
# define _DIM_ "\e[2m"
# define _UNDERLINED_ "\e[4m"
# define _BLINK_ "\e[5m"
# define _REVERSE_ "\e[7m"
# define _HIDDEN_ "\e[8m"

# define _EOATTRIBUTES_ "\e[20m"
# define _EOBOLD_ "\e[21m"
# define _EODIM_ "\e[22m"
# define _EOUNDERLINED_ "\e[24m"
# define _EOBLINK_ "\e[25m"
# define _EOREVERSE_ "\e[27m"
# define _EOHIDDEN_ "\e[28m"

# define _EOFORMAT_ "\e[0m"

typedef int	(*t_fnct)(int *, va_list *, int);

# ifdef __GNUC__

int				ft_printf(const char *restrict
		format, ...) __attribute__((format(printf,1,2)));
int				ft_dprintf(int fd, const char *restrict
		format, ...) __attribute__((format(printf,2,3)));
# else

int				ft_printf(const char *restrict format, ...);
int				ft_dprintf(int fd, const char *restrict format, ...);

# endif

int				ft_vprintf(const char *restrict format, va_list ap);
int				ft_vdprintf(int fd, const char *restrict format, va_list ap);

int				ft_parser(const char *restrict format, va_list *args, int fd);
void			ft_getprec(char *flags, int *flist, va_list *a);
char			*ft_strset(int n, char c);
char			*ft_fill_zero(int *flist, char *s, int minus);

int				flagd(int *flist, va_list *a, int fd);
int				flago(int *flist, va_list *a, int fd);
int				flagf(int *flist, va_list *a, int fd);
int				flagxup(int *flist, va_list *a, int fd);
int				flagx(int *flist, va_list *a, int fd);
int				flagb(int *flist, va_list *a, int fd);
int				flags(int *flist, va_list *a, int fd);
int				flagc(int *flist, va_list *a, int fd);
int				flagu(int *flist, va_list *a, int fd);
int				flaguup(int *flist, va_list *a, int fd);
int				flagp(int *flist, va_list *a, int fd);
int				flagsup(int *flist, va_list *a, int fd);
int				flagcup(int *flist, va_list *a, int fd);
int				flagdup(int *flist, va_list *a, int fd);
int				flagoup(int *flist, va_list *a, int fd);
int				flagfup(int *flist, va_list *a, int fd);
int				flagpercent(int *flist, va_list *a, int fd);
int				flagadd(t_fnct *fnct, va_list *a, int fd);
int				format_numb(int *flist, char *str, int fd);
char			*printf_get_int(int *flist, va_list *a);
char			*printf_get_uint(int *flist, va_list *a, int base);
void			ft_init_funk(t_fnct *ret);

#endif

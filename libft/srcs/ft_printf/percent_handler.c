/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   percent_handler.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/02 13:09:24 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/11 14:28:23 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>
#include "libft.h"
#include "ft_printf.h"

int	flagpercent(int *flist, va_list *a, int fd)
{
	char *str;

	(void)a;
	if (!(str = ft_strdup("%")))
		return (-1);
	flist['.'] = -1;
	flist[' '] = -1;
	flist['+'] = -1;
	return (format_numb(flist, str, fd));
}

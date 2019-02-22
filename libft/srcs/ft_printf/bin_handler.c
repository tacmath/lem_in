/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bin_handler.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/04 18:20:17 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/10 10:56:31 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int			flagb(int *flist, va_list *a, int fd)
{
	char		*str;

	flist[(int)'+'] = 0;
	flist[(int)' '] = 0;
	if (!(str = printf_get_uint(flist, a, 2)))
		return (-1);
	return (format_numb(flist, str, fd));
}

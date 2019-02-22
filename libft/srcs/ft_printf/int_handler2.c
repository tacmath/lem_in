/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   int_handler2.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/05 09:29:23 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/08 15:12:21 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"

int	flagoup(int *flist, va_list *a, int fd)
{
	flist['l'] = 1;
	return (flago(flist, a, fd));
}

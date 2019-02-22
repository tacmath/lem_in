/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/29 17:53:07 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/11 09:29:16 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include "libft.h"

char			*ft_strset(int n, char c)
{
	int		i;
	char	*s;

	i = -1;
	if (n < 0)
		n = 0;
	if (!(s = ft_strnew(n)))
		return (NULL);
	while (++i < n)
		s[i] = c;
	return (s);
}

static int		compute_zero(int *flist, char *s, int minus)
{
	int		len;
	int		temp;
	int		size;

	len = ft_strlen(s);
	if (s[0] == '0')
		flist['#'] = -1;
	if (!(flist['#'] > 0) && minus != 3)
		minus = 0;
	minus = minus == 3 ? 2 : minus;
	temp = 0;
	size = flist['.'];
	if (size == -1)
		temp = flist['0'] > 0 && flist['-'] < 1 ? flist['w'] - minus : 0;
	size = minus == 1 && flist['#'] > 0 ? size - 1 : size;
	if (size < 0)
		size = temp;
	size = size - len;
	return (size);
}

char			*ft_fill_zero(int *flist, char *s, int minus)
{
	char	*filler;
	int		size;

	if (!s)
		return (NULL);
	size = compute_zero(flist, s, minus);
	if (size > 0)
	{
		filler = ft_strset(size, '0');
		if (!filler)
			return (s);
		s = ft_strjoin_free(filler, s);
	}
	flist['0'] = -1;
	flist['.'] = -1;
	return (s);
}

char			*printf_get_int(int *flist, va_list *ap)
{
	char *ret;

	if (flist['j'] > 0)
		ret = ft_jitoa(va_arg(*ap, intmax_t));
	else if (flist['l'] > 1)
		ret = ft_llitoa(va_arg(*ap, long long int));
	else if (flist['z'] > 0)
		ret = ft_zitoa(va_arg(*ap, ssize_t));
	else if (flist['l'] == 1)
		ret = ft_litoa(va_arg(*ap, long int));
	else if (flist['h'] > 1)
		ret = ft_itoa((int)(char)va_arg(*ap, int));
	else if (flist['h'] > 0)
		ret = ft_itoa((int)(short int)va_arg(*ap, int));
	else
		ret = ft_itoa(va_arg(*ap, int));
	return (ret);
}

char			*printf_get_uint(int *flist, va_list *ap, int base)
{
	char *ret;

	if (flist['j'] > 0)
		ret = ft_juitoa_base(va_arg(*ap, uintmax_t), base);
	else if (flist['l'] > 1)
		ret = ft_lluitoa_base(va_arg(*ap, unsigned long long int), base);
	else if (flist['z'] > 0)
		ret = ft_zuitoa_base(va_arg(*ap, size_t), base);
	else if (flist['l'] == 1)
		ret = ft_luitoa_base(va_arg(*ap, unsigned long int), base);
	else if (flist['h'] > 1)
		ret = ft_uitoa_base((unsigned int)(unsigned char)
				va_arg(*ap, unsigned int), base);
	else if (flist['h'] > 0)
		ret = ft_uitoa_base((unsigned int)(unsigned short int)
				va_arg(*ap, unsigned int), base);
	else
		ret = ft_uitoa_base(va_arg(*ap, unsigned int), base);
	return (ret);
}

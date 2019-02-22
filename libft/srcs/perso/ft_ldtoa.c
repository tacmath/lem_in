/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ldtoa.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/02 13:26:12 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/10 09:14:42 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>
#include <stdlib.h>

/*
** https://en.wikipedia.org/wiki/Double-precision_floating-point_format
** this function checks for special cases like nan or +-infinity
** well same things but with long double
*/

static char			*ft_midnight_special(long double nbr)
{
	uint64_t	mantissa;
	uint64_t	*tmp;
	int			exponent;
	char		sign;

	tmp = (uint64_t *)&nbr;
	mantissa = (tmp[0]);
	exponent = ((tmp[1] & 0x7FFF));
	sign = (((tmp[1]) << 48) >> 63);
	if (exponent == 0x7FFF)
	{
		if (sign == 1 && (mantissa == 0 || mantissa == 0x8000000000000000))
			return ("-inf");
		else if (mantissa == 0 || mantissa == 0x8000000000000000)
			return ("inf");
		else
			return ("nan");
	}
	else if (mantissa == 0 && exponent == 0 && sign == 1)
		return ("-0");
	return (NULL);
}

static long double	ft_get_rounder(int preci, char *s)
{
	int tmp;

	tmp = 0;
	tmp = s[ft_strlen(s) - 1] - '0';
	return (preci == -667 && tmp % 2 == 0 ? 4.9L : 5.0L);
}

static	char		*ft_final_rounding(char *ret, char neg)
{
	char *temp;

	temp = ret;
	if (!(ret = ft_strnew(ft_strlen(ret))))
		return (NULL);
	if (neg)
		ret[0] = '-';
	ret[(int)neg] = '1';
	ft_strcpy((ret + 1 + neg), temp + neg);
	free(temp);
	return (ret);
}

static	char		*ft_rounding(char *ret, long double nbr, int preci)
{
	int		i;
	int		carry;
	char	neg;

	neg = ft_strchr(ret, '-') != NULL;
	i = ft_strlen(ret) - 1;
	nbr = nbr < 0 ? nbr * -10 + ft_get_rounder(preci, ret) :
		nbr * 10 + ft_get_rounder(preci, ret);
	if (nbr < 10)
		return (ret);
	carry = 1;
	while (carry != 0 && i >= neg)
	{
		if (ret[i] != '.')
			ret[i] += 1;
		if (ret[i] == '9' + 1)
			ret[i] = '0';
		else if (ret[i] != '.')
			carry = 0;
		i--;
	}
	if (carry == 1)
		ret = ft_final_rounding(ret, neg);
	return (ret);
}

char				*ft_ldtoa(long double d, int prec)
{
	char	*ret;
	char	*temp;

	prec = prec < 0 ? 6 : prec;
	if ((ret = ft_midnight_special(d)) != NULL)
		return (ft_strdup(ret));
	if ((ret = ft_ldtoat(d)) == NULL)
		return (NULL);
	if (prec != 0 && ((ret = ft_strjoin_free(ret, ft_strdup("."))) == NULL))
		return (NULL);
	d = ft_ldbl_get_deci(d);
	prec = prec == 0 ? -666 : prec + 1;
	while (--prec > 0)
	{
		d = d < 0 ? d * -10 : d * 10;
		if ((temp = ft_itoa((int)(d))) == NULL)
			free(ret);
		if (temp == NULL)
			return (NULL);
		if ((ret = ft_strjoin_free(ret, temp)) == NULL)
			return (NULL);
		d = d - (int)d;
	}
	return (ft_rounding(ret, d, prec));
}

/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_dtoa.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/05 12:32:30 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/23 16:28:09 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>
#include <stdlib.h>

/*
** https://en.wikipedia.org/wiki/Double-precision_floating-point_format
** this function checks for special cases like nan or +-infinity
*/

static char		*ft_midnight_special(double nbr)
{
	uint64_t	mantissa;
	uint64_t	*tmp;
	int			exponent;
	char		sign;

	tmp = (uint64_t *)&nbr;
	mantissa = (*tmp & 0xFFFFFFFFFFFFF);
	exponent = ((*tmp & 0x7FF0000000000000) >> 52);
	sign = ((*tmp & 0x8000000000000000) >> 63);
	if (exponent == 0x7FF)
	{
		if (sign == 1 && mantissa == 0)
			return ("-inf");
		else if (mantissa == 0)
			return ("inf");
		else if (mantissa == 1 || mantissa == 0x8000000000001 ||
				mantissa == 0x8000000000000 || mantissa == 0xFFFFFFFFFFFFF)
			return ("nan");
	}
	else if (mantissa == 0 && exponent == 1)
		return ("-0");
	return (NULL);
}

static	char	*ft_final_rounding(char *ret, char neg)
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

static	char	*ft_rounding(char *ret, double nbr)
{
	int		i;
	int		carry;
	char	neg;

	neg = ft_strchr(ret, '-') != NULL;
	i = ft_strlen(ret) - 1;
	nbr = nbr < 0 ? nbr * -10 + 0.5 : nbr * 10 + 0.5;
	if (nbr < 6)
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

char			*ft_dtoa(double nbr, int prec)
{
	char	*ret;
	char	*temp;

	prec = prec == -1 ? 6 : prec;
	if ((ret = ft_midnight_special(nbr)) != NULL)
		return (ft_strdup(ret));
	if ((ret = ft_dtoat(nbr)) == NULL)
		return (NULL);
	if (prec != 0 && ((ret = ft_strjoin_free(ret, ft_strdup("."))) == NULL))
		return (NULL);
	nbr = ft_dbl_get_deci(nbr);
	while (prec > 0)
	{
		nbr = nbr < 0 ? nbr * -10 : nbr * 10;
		if ((temp = ft_itoa((int)nbr)) == NULL)
		{
			free(ret);
			return (NULL);
		}
		if ((ret = ft_strjoin_free(ret, temp)) == NULL)
			return (NULL);
		prec -= 1;
		nbr = nbr - (int)nbr;
	}
	return (ft_rounding(ret, nbr));
}

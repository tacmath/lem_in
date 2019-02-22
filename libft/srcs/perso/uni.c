/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   uni.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/05 13:17:33 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/12 09:43:25 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <unistd.h>
#include <wchar.h>
#include "libft.h"

static int		ft_count_wsize(wchar_t *s)
{
	int size;
	int plus;

	size = 0;
	while (*s != 0)
	{
		if (*s < 128)
			plus = 1;
		else if (*s < 2048)
			plus = 2;
		else if (*s < 65536)
			plus = 3;
		else if (*s <= 0x10FFFF)
			plus = 4;
		else
			return (-1);
		s++;
		size += plus;
	}
	return (size);
}

static void		ft_handle_wchar2(wchar_t wc, unsigned char **s)
{
	unsigned char mask0;
	unsigned char mask1;

	mask0 = 192;
	mask1 = 128;
	**s = mask0 | (((unsigned int)(wc >> 6) << 27) >> 27);
	*(++(*s)) = (unsigned char)(mask1 | ((unsigned int)(wc << 26) >> 26));
}

static void		ft_handle_wchar3(wchar_t wc, unsigned char **s)
{
	unsigned char mask0;
	unsigned char mask1;

	mask0 = 224;
	mask1 = 128;
	**s = mask0 | (((unsigned int)(wc >> 12) << 28) >> 28);
	*(++(*s)) = mask1 | (((unsigned int)(wc >> 6) << 26) >> 26);
	*(++(*s)) = mask1 | (unsigned int)(wc << 26) >> 26;
}

static void		ft_handle_wchar4(wchar_t wc, unsigned char **s)
{
	unsigned char mask0;
	unsigned char mask1;

	mask0 = 240;
	mask1 = 128;
	**s = mask0 | (((wc >> 18) << 29) >> 29);
	*(++(*s)) = mask1 | (((unsigned int)(wc >> 12) << 26) >> 26);
	*(++(*s)) = mask1 | (((unsigned int)(wc >> 6) << 26) >> 26);
	*(++(*s)) = mask1 | ((unsigned int)(wc << 26) >> 26);
}

unsigned char	*ft_handle_wchar(wchar_t *ws)
{
	int				size;
	unsigned char	*s;

	if (ws == NULL)
		return (NULL);
	if ((size = ft_count_wsize(ws)) < 1)
		return (size == -1 ? NULL : (unsigned char*)ft_memalloc(1));
	if (!(s = ft_memalloc(sizeof(char) * (size + 1))))
		return (NULL);
	while (*ws)
	{
		if (*ws < 128)
			*s = *ws;
		else if (*ws < 2048)
			ft_handle_wchar2(*ws, &s);
		else if (*ws < 65536)
			ft_handle_wchar3(*ws, &s);
		else
			ft_handle_wchar4(*ws, &s);
		s++;
		ws++;
	}
	return (s - size);
}

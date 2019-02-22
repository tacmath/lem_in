/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putendl.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/06 15:13:38 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/08 09:19:03 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putendl(const char *str)
{
	if (str)
	{
		write(1, str, ft_strlen(str));
		ft_putchar('\n');
	}
}

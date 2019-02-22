/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstdel.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/04 10:35:14 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/04 13:29:16 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *tmp;

	if (*alst && alst)
	{
		while (*alst)
		{
			tmp = (*alst)->next;
			if (del)
				del((*alst)->content, (*alst)->content_size);
			free(*alst);
			*alst = tmp;
		}
	}
}

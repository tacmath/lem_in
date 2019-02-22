/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstnew.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/04 09:29:18 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 09:56:52 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*lst;

	if (!(lst = malloc(sizeof(*lst))))
		return (NULL);
	if (content)
	{
		if (!(lst->content = malloc(content_size)))
			return (NULL);
		ft_memcpy(lst->content, content, content_size);
		lst->content_size = content_size;
	}
	else
	{
		lst->content = NULL;
		lst->content_size = 0;
	}
	lst->next = NULL;
	return (lst);
}

/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstmap.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/04 12:25:38 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/15 14:11:00 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*tmp;
	t_list	*new;

	if (!lst || !f)
		return (NULL);
	if (!(new = f(lst)))
		return (NULL);
	tmp = new;
	lst = lst->next;
	while (lst)
	{
		if (!(new->next = f(lst)))
			return (NULL);
		new = new->next;
		lst = lst->next;
	}
	new->next = NULL;
	return (tmp);
}

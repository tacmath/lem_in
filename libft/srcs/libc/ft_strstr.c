/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strstr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/02 16:28:57 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/06 15:38:11 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

char	*ft_strstr(const char *str, const char *to_find)
{
	int i;
	int pos;

	i = 1;
	pos = -1;
	if (to_find[0] == '\0')
		return ((char *)str);
	while (str[++pos])
	{
		if (str[pos] == to_find[0])
		{
			while (str[pos + i] == to_find[i] && to_find[i] && to_find != '\0')
				i++;
			if (to_find[i] == '\0')
				return ((char *)&str[pos]);
			i = 1;
		}
	}
	return (0);
}

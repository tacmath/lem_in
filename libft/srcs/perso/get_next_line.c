/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/18 11:54:58 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/02/21 15:03:16 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static char	*strjoin(char *s1, char *s2, int total, int ret)
{
	char	*str;
	int		n;

	if (!(s1 && s2))
		return (0);
	if (!(str = malloc(sizeof(char) * (total + 1))))
		return (0);
	n = -1;
	str = ft_strcpy(str, s1);
	while (s2[++n])
		str[total - ret + n] = s2[n];
	str[total - ret + n] = '\0';
	free(s1);
	return (str);
}

static void	get_all(const int fd, char **mem)
{
	int		ret;
	int		total;
	char	buf[BUFF_SIZE + 1];

	total = -1;
	while (mem[fd][++total])
		if (mem[fd][total] == '\n')
			return ;
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		total += ret;
		mem[fd] = strjoin(mem[fd], buf, total, ret);
		total -= ret;
		while (mem[fd][total])
			if (mem[fd][total++] == '\n')
				return ;
	}
	if (!mem[fd])
		mem[fd] = ft_memalloc(1);
}

int			get_next_line(const int fd, char **line)
{
	static char	*mem[4864];
	int			n;
	char		*tmp;

	n = -1;
	tmp = 0;
	if (BUFF_SIZE < 1 || read(fd, 0, 0) < 0 || !line || fd < 0)
		return (-1);
	if (!mem[fd])
		mem[fd] = ft_memalloc(1);
	get_all(fd, mem);
	while (mem[fd][++n] != '\n' && mem[fd][n] != '\0')
		;
	if (n == 0 && mem[fd][n] == '\0')
	{
		ft_strdel(&mem[fd]);
		return (0);
	}
	*line = ft_strsub(mem[fd], 0, n);
	tmp = ft_strdup(mem[fd]);
	ft_memdel((void**)&mem[fd]);
	mem[fd] = ft_strsub(tmp, n + 1, ft_strlen(&tmp[n + 1]));
	ft_memdel((void**)&tmp);
	return (1);
}

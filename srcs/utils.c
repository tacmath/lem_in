/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/14 14:21:16 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 15:00:55 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

int			add_to_output(char ***output, char *new_line)
{
	int		len;
	char	**tmp;
	int		n;

	len = -1;
	while ((*output)[++len] != 0)
		;
	if (!(tmp = malloc(sizeof(char*) * (len + 2))))
		return (0);
	n = -1;
	while (++n < len)
		tmp[n] = (*output)[n];
	tmp[n] = new_line;
	tmp[n + 1] = 0;
	free(*output);
	*output = tmp;
	return (1);
}

void		write_output(t_map *map, char **output)
{
	int n;
	int len;

	n = -1;
	while (output[++n] != 0)
	{
		if (!map->correction || (output[n][0] == '#' && output[n][1] != '#'))
		{
			len = ft_strlen(output[n]);
			output[n][len] = '\n';
			write(1, output[n], len + 1);
		}
		free(output[n]);
	}
	free(output);
	output = 0;
	ft_putchar('\n');
}

int			isroom(char *str)
{
	int n;

	if (str[0] == 'L' && str[0] == ' ')
		return (0);
	n = -1;
	while (str[++n] != ' ')
		if (str[n] == '\0')
			return (0);
	while (str[++n] != ' ')
		if (str[n] < '0' || str[n] > '9')
			return (0);
	while (str[++n])
		if (str[n] < '0' || str[n] > '9')
			return (0);
	return (1);
}

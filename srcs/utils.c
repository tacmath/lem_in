/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/14 14:21:16 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/06 17:29:05 by lperron     ###    #+. /#+    ###.fr     */
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

	n = -1;
	while (output[++n] != 0)
	{
		if (!map->correction || (output[n][0] == '#' && output[n][1] != '#'))
			ft_putendl(output[n]);
		free(output[n]);
	}
	free(output);
	output = 0;
}

static int	gou_lag(t_map *map, int room1, int room2)
{
	int n;
	int m;
	int i;
	int *tmp;

	map->room[room1].nb_connection--;
	n = map->room[room1].nb_connection;
	if (!(tmp = malloc(sizeof(int) * (n))))
		return (0);
	m = -1;
	i = 0;
	while (++m <= n)
		if (map->room[room1].connection[m] != room2)
			tmp[m - i] = map->room[room1].connection[m];
		else
			i++;
	free(map->room[room1].connection);
	map->room[room1].connection = tmp;
	return (1);
}

int			sta_line(t_map *map, int room1, int room2)
{
	int n;
	int m;
	int i;
	int *tmp;

	map->room[room1].nb_connection--;
	n = map->room[room1].nb_connection;
	if (!(tmp = malloc(sizeof(int) * (n))))
		return (0);
	m = -1;
	i = 0;
	while (++m <= (n))
	{
		if (map->room[room1].connection[m] != room2)
		{
			tmp[m - i] = map->room[room1].connection[m];
		}
		else
			i++;
	}
	free(map->room[room1].connection);
	map->room[room1].connection = tmp;
	if (!gou_lag(map, room2, room1))
		return (0);
	return (1);
}

int		isroom(char *str)
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

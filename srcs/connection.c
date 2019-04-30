/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   connection.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/17 15:21:32 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 16:12:18 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

static int	*connection_realloc(int *connection, int *nb_co, int new_co)
{
	int n;
	int *tmp;

	n = -1;
	while (++n < *nb_co)
		if (connection[n] == new_co)
			return (connection);
	(*nb_co)++;
	if (!(tmp = malloc(sizeof(int) * (*nb_co))))
		return (0);
	n = -1;
	while (++n < (*nb_co - 1))
		tmp[n] = connection[n];
	tmp[n] = new_co;
	free(connection);
	return (tmp);
}

static int	get_connection(t_map *map, char *line, char ***output)
{
	int co1;
	int co2;
	int len;

	len = -1;
	while (line[++len] != '-')
		;
	co1 = -1;
	while (ft_strncmp(map->room[++co1].name, line, len)
		&& co1 < map->nb_room - 1)
		;
	co2 = -1;
	while (ft_strcmp(map->room[++co2].name, &(line[len + 1]))
		&& co2 < map->nb_room - 1)
		;
	if (ft_strncmp(map->room[co1].name, line, len) ||
	ft_strcmp(map->room[co2].name, &(line[len + 1])))
		return (-!(ft_super_free(1, line)));
	if (!(map->room[co1].connection = connection_realloc(map->room
	[co1].connection, &(map->room[co1].nb_connection), co2)) ||
	!(map->room[co2].connection = connection_realloc(map->room[co2].connection,
	(&map->room[co2].nb_connection), co1)))
		return (0);
	return (!add_to_output(output, line) ? 0 : 1);
}

int			get_all_connection(t_map *map, char *line, char ***output)
{
	int ret;

	if ((ret = 0) || !rooms_init(map) || (ft_strchr(line, '-') &&
		!(ret = get_connection(map, line, output))))
		return (ret == 0 ? ft_super_free(1, line) : 0);
	if (ret == -1)
		return (1);
	while (get_next_line(0, &line) == 1)
	{
		if (ft_strchr(line, '-') && line[0] != '#')
		{
			if (!(ret = get_connection(map, line, output)))
				return (0);
			if (ret == -1)
				return (1);
		}
		else if (line[0] != '#')
		{
			free(line);
			return (1);
		}
		else if (!add_to_output(output, line))
			return (0);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/21 15:34:46 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/16 17:15:37 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

int		*connection_realloc(int *connection, int *nb_co, int new_co)
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

int		get_connection(t_map *map, char *line, char ***output)
{
	int co1;
	int co2;
	int len;

	len = -1;
	while (line[++len] != '-')
		;
	co1 = -1;
	while (ft_strncmp(map->room[++co1].name, line, len) && co1 < map->nb_room)
		;
	co2 = -1;
	while (ft_strcmp(map->room[++co2].name, &(line[len + 1])) &&
			co2 < map->nb_room)
		;
	if (ft_strncmp(map->room[co1].name, line, len) ||
ft_strcmp(map->room[co2].name, &(line[len + 1])) ||
!(map->room[co1].connection = connection_realloc(map->room[co1].connection,
&(map->room[co1].nb_connection), co2)))
		return (0);
	if (!(map->room[co2].connection =
				connection_realloc(map->room[co2].connection,
					(&map->room[co2].nb_connection), co1)))
		return (0);
	return (!add_to_output(output, line) ? 0 : 1);
}

int		get_all_connection(t_map *map, char *line, char ***output)
{
	if (!rooms_init(map))
		return (0);
	if (!get_connection(map, line, output))
		return (0);
	while (get_next_line(0, &line) == 1)
	{
		if (ft_strchr(line, '-') && line[0] != '#')
		{
			if (!get_connection(map, line, output))
				return (0);
		}
		else if (!add_to_output(output, line))
			return (0);
	}
	return (1);
}

int		test_room(t_map *map, int room)
{
	int n;

	if (room == map->start || room == map->end)
		return (1);
	map->room[room].heat = 1;
	n = -1;
	while (++n < map->room[room].nb_connection)
	{
		if (map->room[map->room[room].connection[n]].heat != 1)
			if (test_room(map, map->room[room].connection[n]))
				return (1);
	}
	return (0);
}

void	test_all_maps(t_map *map)
{
	int m;

	m = -1;
	while (++m < map->room[map->end].nb_connection)
		if (!test_room(map, map->room[map->end].connection[m]))
			sta_line(map, map->end, map->room[map->end].connection[m]);
}

int		remove_useless_co(t_map *map)
{
	int n;

	n = -1;
	while (++n < map->room[map->start].nb_connection)
		if (map->room[map->room[map->start].connection[n]].heat == -1 &&
				!sta_line(map, map->start, map->room[map->start].connection[n]))
			return (0);
	return (1);
}

int		main(void)
{
	t_map	*map;
	char	**output;
	int		n;

	output = 0;
	if (!(map = malloc(sizeof(t_map))) || !init_struct(map, &output)
			|| !get_room(map, &output))
		return (-1);
	n = -1;
	if (!get_error(map))
	{
		while (output[++n] != 0)
			free(output[n]);
		free(output);
		return (-1);
	}
	write_output(output);
	ft_putchar('\n');
	if (!remove_useless_co(map))
		return (-1);
	get_multiple_path(map);
	free_map(map);
	return (0);
}

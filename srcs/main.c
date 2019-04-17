/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/21 15:34:46 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/17 14:12:22 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

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
	if (!remove_useless_co(map) || !get_multiple_path(map))
		return (-1);
	gogogo(map);
	free_map(map);
	return (0);
}

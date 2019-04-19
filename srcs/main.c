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

int		main(int ac, char **av)
{
	t_map	*map;
	char	**output;
	int		n;

	output = 0;
	if (!(map = malloc(sizeof(t_map))) || !init_struct(map, &output)
			|| !get_room(map, &output))
		return (-1);
	n = 0;
	while (++n < ac)
		if (av[n][0] == '-' && av[n][1] == 'c' && av[n][2] == '\0')
			map->correction = 1;
	n = -1;
	if (!get_error(map))
	{
		while (output[++n] != 0)
			free(output[n]);
		free(output);
		return (-1);
	}
	write_output(map, output);
	ft_putchar('\n');
	if (!remove_useless_co(map) || !get_multiple_path(map))
		return (-1);
	gogogo(map);
	free_map(map);
	return (0);
}

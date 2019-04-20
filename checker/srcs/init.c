/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/14 14:24:10 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/17 14:11:37 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "checker.h"

int			rooms_init(t_map *map)
{
	int n;

	n = -1;
	while (++n < map->nb_room)
	{
		map->room[n].connection = 0;
		map->room[n].nb_connection = 0;
		map->room[n].ant = 0;
	}
	map->room[map->start].ant = 1;
	n = -1;
	if (!(map->ant = malloc(sizeof(int) * map->nb_ant)))
		return (0);
	while (++n < map->nb_ant)
		map->ant[n] = map->start;
	return (1);
}

int			init_struct(t_map *map)
{
	char *line;

	if (get_next_line(0, &line) < 1)
		return (0);
	map->nb_ant = ft_atoi(line);
	if (map->nb_ant <= 0)
	{
		free(line);
		free(map);
		ft_putendl("ERROR : wrong number of ant");
		return (0);
	}
	free(line);
	map->room = 0;
	map->start = -1;
	map->end = -1;
	return (1);
}

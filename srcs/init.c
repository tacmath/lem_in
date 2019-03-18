/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/14 14:24:10 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/18 16:29:44 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

int		rooms_init(t_map *map)
{
	int n;

	n = -1;
	while (++n < map->nb_room)
	{
		map->room[n].connection = 0;
		map->room[n].heat = -1;
		map->room[n].hype = 0;
		map->room[n].ant = 0;
		map->room[n].nb_connection = 0;
	}
	n = -1;
	while (++n < map->nb_ant)
	{
		map->ant[n] = map->start;
		map->last_room[n] = map->start;
	}
	return (1);
}

int		init_struct(t_map *map, char ***output)
{
	char *line;

	if (!(*output = ft_memalloc(sizeof(char*))))
		return (-1);
	if (get_next_line(0, &line) < 1)
		return (0);
	map->nb_ant = ft_atoi(line);
	if (!(add_to_output(output, line)))
		return (0);
	if (map->nb_ant <= 0)
	{
		free(*(output)[0]);
		free(*output);
		free(map);
		ft_putendl("ERROR");
		return (0);
	}
	if (!(map->ant = malloc(sizeof(int) * map->nb_ant)))
		return (ft_super_free(1, map));
	if (!(map->last_room = malloc(sizeof(int) * map->nb_ant)))
		return (ft_super_free(1, map));
	map->room = 0;
	map->start = -1;
	map->end = -1;
	return (1);
}

/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   room.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/14 14:13:45 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/16 16:41:31 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "checker.h"

static char	*get_room_name(char *line)
{
	int		n;
	char	*name;

	n = -1;
	while (line[++n] != ' ')
		;
	if (!(name = malloc(sizeof(char) * (n + 1))))
		return (0);
	n = -1;
	while (line[++n] != ' ')
		name[n] = line[n];
	name[n] = '\0';
	free(line);
	return (name);
}

static int	room_realloc(t_map *map, char *line)
{
	int		n;
	t_room	*tmp;

	map->nb_room++;
	if (!(tmp = malloc(sizeof(t_room) * map->nb_room)))
		return (0);
	n = -1;
	while (++n < map->nb_room - 1)
		tmp[n].name = map->room[n].name;
	if (!(tmp[n].name = get_room_name(line)))
		return (0);
	free(map->room);
	map->room = tmp;
	return (1);
}

static int	get_start_and_end(t_map *map, char *line)
{
	if (!ft_strcmp(line, "##start"))
	{
		free(line);
		if (get_next_line(0, &line) < 1)
			return (0);
		map->start = map->nb_room;
		if (!room_realloc(map, line))
			return (0);
	}
	else
	{
		free(line);
		if (get_next_line(0, &line) < 1)
			return (0);
		map->end = map->nb_room;
		if (!room_realloc(map, line))
			return (0);
	}
	return (1);
}

int			get_room(t_map *map)
{
	char	*line;

	map->nb_room = 0;
	if (get_next_line(0, &line) < 1)
		return (0);
	while (isroom(line) || line[0] == '#')
	{
		if (line[0] != '#')
		{
			if (!room_realloc(map, line))
				return (0);
		}
		else if (!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end"))
		{
			if (!get_start_and_end(map, line))
				return (0);
		}
		else
			free(line);
		if (get_next_line(0, &line) < 1)
			return (0);
	}
	if (!get_all_connection(map, line))
		return (0);
	return (1);
}

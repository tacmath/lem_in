/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   room.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/07 13:47:21 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/07 15:41:18 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visual.h"

static t_room	get_room_info(char *line)
{
	int		n;
	t_room	room;

	n = -1;
	while (line[++n] != ' ')
		;
	if (!(room.name = malloc(sizeof(char) * (n + 1))))
	{
		room.name = 0;
		return (room);
	}
	room.x = ft_atoi(&(line[n]));
	while (line[++n] != ' ')
		;
	room.y = ft_atoi(&(line[n]));
	n = -1;
	while (line[++n] != ' ')
		room.name[n] = line[n];
	room.name[n] = '\0';
	free(line);
	return (room);
}

static int		room_realloc(t_map *map, char *line)
{
	int		n;
	t_room	*tmp;

	map->nb_room++;
	if (!(tmp = malloc(sizeof(t_room) * map->nb_room)))
		return (0);
	n = -1;
	while (++n < map->nb_room - 1)
	{
		tmp[n].name = map->room[n].name;
		tmp[n].x = map->room[n].x;
		tmp[n].y = map->room[n].y;
	}
	tmp[n] = get_room_info(line);
	if (tmp[n].name == 0)
		return (0);
	free(map->room);
	map->room = tmp;
	return (1);
}

static int		get_start_and_end(t_map *map, char *line)
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

int				get_room(t_map *map)
{
	char	*line;

	map->nb_room = 0;
	if (get_next_line(0, &line) < 1)
		return (0);
	while (ft_strchr(line, ' ') || line[0] == '#')
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

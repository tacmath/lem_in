/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   room.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/14 14:13:45 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 16:08:03 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

static char	*get_room_name(char *line, char ***output)
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
	if (!add_to_output(output, line))
		return (0);
	return (name);
}

static int	room_realloc(t_map *map, char *line, char ***output)
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
		tmp[n].connection = 0;
	}
	if (!(tmp[n].name = get_room_name(line, output)))
		return (0);
	tmp[n].connection = 0;
	free(map->room);
	map->room = tmp;
	return (1);
}

static int	get_start_and_end(t_map *map, char *line, char ***output)
{
	if (!ft_strcmp(line, "##start"))
	{
		if (!add_to_output(output, line))
			return (0);
		if (get_next_line(0, &line) < 1)
			return (0);
		if (!isroom(line))
			return (ft_super_free(1, line));
		map->start = map->nb_room;
		if (isroom(line) && !room_realloc(map, line, output))
			return (0);
	}
	else
	{
		if (!add_to_output(output, line))
			return (0);
		if (get_next_line(0, &line) < 1)
			return (0);
		if (!isroom(line))
			return (ft_super_free(1, line));
		map->end = map->nb_room;
		if (!room_realloc(map, line, output))
			return (0);
	}
	return (1);
}

int			get_room(t_map *map, char ***output)
{
	char	*line;

	map->nb_room = 0;
	if (get_next_line(0, &line) < 1)
		return (0);
	while (isroom(line) || line[0] == '#')
	{
		if (line[0] != '#')
		{
			if (!room_realloc(map, line, output))
				return (0);
		}
		else if (!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end"))
		{
			if (!get_start_and_end(map, line, output))
				return (0);
		}
		else if (!add_to_output(output, line))
			return (0);
		if (get_next_line(0, &line) < 1)
			return (0);
	}
	if (!get_all_connection(map, line, output))
		return (0);
	return (1);
}

void		get_room_heat(t_map *map, int room)
{
	int	n;
	int	co;

	map->room[room].heat = 1;
	if (room == map->start)
		return ;
	n = -1;
	while (++n < map->room[room].nb_connection)
	{
		co = map->room[room].connection[n];
		if (map->room[co].heat == -1)
			get_room_heat(map, co);
	}
}

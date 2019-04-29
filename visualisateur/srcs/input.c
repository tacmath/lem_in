/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/21 15:34:46 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/07 15:04:13 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visual.h"

static int	get_connection(t_map *map, char *line)
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
	while (ft_strcmp(map->room[++co2].name, &(line[len + 1]))
		&& co2 < map->nb_room)
		;
	draw_pipe(map, co1, co2);
	free(line);
	return (1);
}

static int	rooms_init(t_map *map)
{
	int n;

	n = -1;
	while (++n < map->nb_ant)
	{
		map->ant[n] = map->start;
		map->ant_goal[n] = -1;
	}
	draw_all_room(map);
	return (1);
}

int			get_all_connection(t_map *map, char *line)
{
	if (!rooms_init(map))
		return (0);
	if (!get_connection(map, line))
		return (0);
	while (get_next_line(0, &line) == 1 && line[0] != '\0')
	{
		if (ft_strchr(line, '-'))
		{
			if (!get_connection(map, line))
				return (0);
		}
		else
			free(line);
	}
	free(line);
	return (1);
}

int			get_info(t_map *map)
{
	char	*line;

	if (get_next_line(0, &line) < 1)
		return (0);
	map->nb_ant = ft_atoi(line);
	free(line);
	if (!(map->ant = malloc(sizeof(int) * map->nb_ant)))
		return (0);
	if (!(map->ant_goal = malloc(sizeof(int) * map->nb_ant)))
		return (0);
	map->room = 0;
	if (!get_room(map))
		return (0);
	return (1);
}

/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/14 14:21:16 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/06 17:29:05 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "checker.h"

int move_ant(t_map *map, char *str)
{
	int n;
	int ant;
	char *name;
	int len;
	int room;

	ant = ft_atoi(str);
	if (ant > map->nb_ant)
	{
		ft_putendl("[KO] invalid output");
		return (0);		
	}
	n = -1;
	while (str[++n] != '-')
		if (str[n] < '0' || str[n] > '9')
		{
			ft_putendl("[KO] invalid output");
			return (0);
		}
	n++;
	len = n;
	while (str[++len] != ' ' && str[len] != '\0')
		;
	len -= n;
	room = 0;
	while ((name = map->room[room].name) && ft_strncmp(&str[n], name, len) && room < map->nb_room - 1)
		room++;
	if (ft_strncmp(&str[n], name, len))
	{
		ft_putendl("[KO] unexisting room used");
		return (0);
	}
	if (map->room[room].ant == 1)
	{
		ft_printf("[KO] already a ant in room %s\n", map->room[room].name);
		return (0);
	}
	if (map->ant[ant - 1] != map->start)
		map->room[map->ant[ant - 1]].ant = 0;
	if (room != map->end)
		map->room[room].ant = 1;
	n = -1;
	while (++n < map->room[map->ant[ant - 1]].nb_connection)
		if (map->room[map->ant[ant - 1]].connection[n] == room)
			map->ant[ant - 1] = room;
	if (map->ant[ant - 1] != room)
	{
		ft_putendl("[KO] unexisting connection used");
		return (0);
	}
	return (1);
}

int check(t_map *map)
{
	char	*line;
	int 	nb_line;
	int 	n;

	nb_line = 0;
	while (get_next_line(0, &line) == 1)
	{
		if (line[0] == 'L')
			nb_line++;
		n = -1;
		while (line[++n])
			if (line[n] == 'L')
				if (!move_ant(map, &line[n + 1]))
					return (1);
		free(line);
	}
	n = -1;
	while (++n < map->nb_ant && map->ant[n] == map->end)
		;
	if (n != map->nb_ant && map->ant[n] != map->end)
	{
		ft_printf("[KO] only %d ants out of %d got to the end\n", n, map->nb_ant);
		return (1);
	}
	ft_printf("[OK] the number of lines used to solve the problem is %d\n", nb_line);
	return (1);
}

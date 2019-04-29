/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/14 14:21:16 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/29 14:16:01 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "checker.h"

int	check_ant(t_map *map, char *str, int *ant)
{
	int n;

	*ant = ft_atoi(str);
	if (*ant > map->nb_ant)
	{
		ft_putendl(_RED_ "[KO] invalid output" _EOC_);
		return (0);
	}
	n = -1;
	while (str[++n] != '-')
		if (str[n] < '0' || str[n] > '9')
		{
			ft_putendl(_RED_"[KO] invalid output" _EOC_);
			return (0);
		}
	n++;
	return (n);
}

int	check_room(t_map *map, char *str, int len, int *room)
{
	char *name;

	*room = 0;
	while ((name = map->room[*room].name) && ft_strncmp(str, name, len)
		&& *room < map->nb_room - 1)
		(*room)++;
	if (ft_strncmp(str, name, len))
		return (!ft_printf(_RED_ "[KO] unexisting room used\n" _EOC_));
	if (map->room[*room].ant == 1)
	{
		return (!ft_printf(_RED_ "[KO] already a ant in room %s\n" _EOC_,
					map->room[*room].name));
	}
	return (1);
}

int	move_ant(t_map *map, char *str)
{
	int		n;
	int		ant;
	int		len;
	int		room;

	if (!(n = check_ant(map, str, &ant)))
		return (0);
	len = n;
	while (str[++len] != ' ' && str[len] != '\0')
		;
	len -= n;
	if (!check_room(map, &str[n], len, &room))
		return (0);
	if (map->ant[ant - 1] != map->start)
		map->room[map->ant[ant - 1]].ant = 0;
	if (room != map->end)
		map->room[room].ant = 1;
	n = -1;
	while (++n < map->room[map->ant[ant - 1]].nb_connection)
		if (map->room[map->ant[ant - 1]].connection[n] == room)
			map->ant[ant - 1] = room;
	if (map->ant[ant - 1] != room)
		return (!ft_printf(_RED_ "[KO] unexisting connection used" _EOC_));
	return (1);
}

int	check(t_map *map)
{
	char	*line;
	int		nb_line;
	int		n;

	nb_line = 0;
	while (get_next_line(0, &line) == 1)
	{
		if (line[0] == 'L')
			nb_line++;
		n = -1;
		while (line[++n])
			if (line[n] == 'L' && !move_ant(map, &line[n + 1]))
				return (1);
		free(line);
	}
	n = -1;
	while (++n < map->nb_ant && map->ant[n] == map->end)
		;
	if (n != map->nb_ant && map->ant[n] != map->end)
	{
		return (ft_printf(_RED_
	"[KO] only %d ants out of %d got to the end\n" _EOC_, n, map->nb_ant));
	}
	return (ft_printf(_GREEN_
"[OK] the number of lines used to solve the problem is %d\n" _EOC_, nb_line));
}

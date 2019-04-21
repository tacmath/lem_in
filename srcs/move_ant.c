/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   move_ant.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/29 12:13:30 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/17 14:37:47 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

int add_ant_to_line(char **line, int ant, char *room_name, int *len)
{
	int n;
	int m;
	char *ant_nb;
	char *tmp;
	
	if (!(ant_nb = ft_itoa(ant + 1)))
		return (0);
	if (!(tmp = malloc(sizeof(int) * (*len + ft_strlen(ant_nb) + 4 + ft_strlen(room_name)))))
		return (0);
	n = -1;
	while (++n < *len)
		tmp[n] = (*line)[n];
	tmp[n] = 'L';
	*len += ft_strlen(ant_nb) + 1;
	m = -1;
	while (++n < *len)
		tmp[n] = ant_nb[++m];
	tmp[n] = '-';
	*len += ft_strlen(room_name) + 1;
	m = -1;
	while (++n < *len)
		tmp[n] = room_name[++m];
	tmp[n] = ' ';
	tmp[n + 1] = '\0';
	*len = n + 1;
	free(*line);
	free(ant_nb);
	*line = tmp;
	return (1);
}

int	continue_path(t_map *map, int ant, char **line, int *line_len)
{
	int j;
	
	j = -1;
	while (++j < ant)
		if (map->ant[j].room != map->end && map->ant[j].room != map->start)
		{
			map->ant[j].i_path++;
			map->ant[j].room = map->path[map->ant[j].path][map->ant[j].i_path];
			if (!map->correction)
				if (!add_ant_to_line(line, j, map->room[map->ant[j].room].name, line_len))
					return (0);
		}
	return (1);
}

int		how_long(t_map *map)
{
	int n;
	int m;
	int nb;

	nb = map->path_len[0] - 1;
	n = map->nb_ant;
	while (n > 0)
	{
		nb++;
		m = -1;
		while (++m < map->nb_path)
			if (map->path_len[m] <= nb)
				n--;
	}
	return (nb);
}

int	can_i_go(t_map *map, int ant, char **line, int *line_len)
{
	int m;
	int n;

	n = -1;
	m = 0;
	while (++n < ant && m < map->nb_path)
		if (map->ant[n].room == map->start)
		{
			if (how_long(map) >= map->path_len[m])
			{
				map->nb_ant--;
				map->ant[n].i_path = 0;
				map->ant[n].path = m;
				map->ant[n].room = map->path[m][0];
				if (!map->correction)
					if (!add_ant_to_line(line, n, map->room[map->path[m][0]].name, line_len))
						return (0);
				if (map->ant[n].room == map->end)
					map->ant[n].room = -1;
			}
			m++;
		}
	return (1);
}

int		gogogo(t_map *map)
{
	int	ant;
	int count;
	char *line;
	int line_len;

	ant = map->nb_ant;
	count = 0;
	while (map->ant[ant - 1].room != map->end)
	{
		line_len = 0;
		line = 0;
		count++;
		if (!continue_path(map, ant, &line, &line_len) ||
			!can_i_go(map, ant, &line, &line_len))
			return (0);
		if (!map->correction)
		{
			line[line_len - 1] = '\n';
			write(1, line, line_len);
			free(line);
		}
	}
	if (map->correction)
		ft_printf("lines = %d\n", count);
	return (1);
}

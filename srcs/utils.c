/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/14 14:21:16 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/15 17:06:20 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

int			add_to_output(char ***output, char *new_line)
{
	int		len;
	char	**tmp;
	int		n;

	len = -1;
	while ((*output)[++len] != 0)
		;
	if (!(tmp = malloc(sizeof(char*) * (len + 2))))
		return (0);
	n = -1;
	while (++n < len)
		tmp[n] = (*output)[n];
	tmp[n] = new_line;
	tmp[n + 1] = 0;
	free(*output);
	*output = tmp;
	return (1);
}

void		write_output(char **output)
{
	int n;

	n = -1;
	while (output[++n] != 0)
	{
		ft_putendl(output[n]);
		free(output[n]);
	}
	free(output);
	output = 0;
}

void		free_map(t_map *map)
{
	int n;

	n = -1;
	while (++n < map->nb_room)
	{
		free(map->room[n].name);
		free(map->room[n].connection);
	}
	free(map->ant);
	free(map->room);
	free(map);
}

static int			gou_lag(t_map *map, int room1, int room2)
{
	int n;
	int m;
	int i;
	int *tmp;

	map->room[room1].nb_connection--;
	n = map->room[room1].nb_connection;
	if (!(tmp = malloc(sizeof(n))))
		return (0);
	m = -1;
	i = 0;
	while (++m < n + 1)
		if (map->room[room1].connection[m] != room2)
		{
			tmp[m - i] = map->room[room1].connection[m];
			i++;
		}
	free(map->room[room1].connection);
	map->room[room1].connection = tmp;
	return (1);
}

int			sta_line(t_map *map, int room1, int room2)
{
	int n;
	int m;
	int i;
	int *tmp;

	map->room[room1].nb_connection--;
	n = map->room[room1].nb_connection;
	if (!(tmp = malloc(sizeof(n))))
		return (0);
	m = -1;
	i = 0;
	while (++m < n + 1)
		if (map->room[room1].connection[m] != room2)
		{
			tmp[m - i] = map->room[room1].connection[m];
			i++;
		}
	free(map->room[room1].connection);
	map->room[room1].connection = tmp;
	if (!gou_lag(map, room2, room1))
		return (0);
	return (1);
}

int			get_error(t_map *map)
{
	if (map->nb_room == 0)
	{
		free(map->ant);
		free(map);
		ft_putendl("ERROR");
		return (0);
	}
	else if (map->start == -1 || map->end == -1)
	{
		free_map(map);
		ft_putendl("ERROR");
		return (0);
	}
	get_room_heat(map, map->end, 0);
	if (map->room[map->start].heat == -1)
	{
		free_map(map);
		ft_putendl("ERROR");
		return (0);
	}
	return (1);
}

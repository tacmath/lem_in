/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   room.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/14 14:13:45 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/20 16:36:32 by mtaquet     ###    #+. /#+    ###.fr     */
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
		tmp[n].name = map->room[n].name;
	if (!(tmp[n].name = get_room_name(line, output)))
		return (0);
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
		map->start = map->nb_room;
		if (!room_realloc(map, line, output))
			return (0);
	}
	else
	{
		if (!add_to_output(output, line))
			return (0);
		if (get_next_line(0, &line) < 1)
			return (0);
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
	while (ft_strchr(line, ' ') || line[0] == '#')
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
		else
			free(line);
		if (get_next_line(0, &line) < 1)
			return (0);
	}
	if (!get_all_connection(map, line, output))
		return (0);
	return (1);
}

void		get_room_heat(t_map *map, int room, int heat)
{
	int	n;
	int	co;

	map->room[room].heat = heat;
	if (room == map->start)
		return ;
	n = -1;
	while (++n < map->room[room].nb_connection)
	{
		co = map->room[room].connection[n];
		if (map->room[co].heat == -1 || map->room[co].heat > heat + 1)
			get_room_heat(map, co, heat + 1);
	}
}

void		reset_heat(t_map *map)
{
	int n;

	n = -1;
	while (++n < map->nb_room)
		map->room[n].heat = -1;
}

int 		get_way(t_map *map, int room, int heat, int **way)
{
	int	n;
	int	co;
	int ret;

	ret = 0;
	map->room[room].heat = heat;
	if (room == map->end)
	{
		free(*way);
		if (!(*way = malloc(sizeof(int) * (heat))))
				return (0);
		(*way)[heat - 1] = -1;
		return (1);
	}
	n = -1;
	while (++n < map->room[room].nb_connection)
	{
		co = map->room[room].connection[n];
		if ((map->room[co].heat == -1 || map->room[co].heat > heat + 1) && (heat + 1 < map->room[map->end].heat || map->room[map->end].heat == -1))
			if (get_way(map, co, heat + 1, way))
				ret++;
	}
	if (ret > 0)
	{
		(*way)[heat - 1] = room;
		return (1);
	}
	return (0);
}

void put_co(int *co, t_map *map)
{
	int n;

	n = -1;
	while (co[++n] != -1)
	{
		ft_putstr(map->room[co[n]].name);
		ft_putchar(' ');
	}
	ft_putendl("");
}

int *no_comp_realloc(int *comp, int new_comp)
{
	int n;
	int *tmp;

	n = -1;
	while (comp[++n] != -1)
		if (comp[n] == new_comp)
			return (comp);
	if (!(tmp = malloc(sizeof(int) * (n + 2))))
		return (0);
	n = -1;
	while (comp[++n] != -1)
		tmp[n] = comp[n];
	tmp[n++] = new_comp;
	tmp[n] = -1;
	free(comp);
	return (tmp);
}

int test_all_way(t_map *map)
{
	int n;
	int m;
	int i;
	int j;
	int nb_way;

	nb_way = map->room[map->start].nb_connection;
	map->comp = malloc(sizeof(int*) * nb_way);
	n = -1;
	while (++n < nb_way)
	{
		map->comp[n] = malloc(sizeof(int));
		map->comp[n][0] = -1;
	}
	n = -1;
	while (++n < nb_way)
	{
		m = -1;
		while (map->way[n] != 0 && map->way[n][++m] != -1)
		{

			i = n;
			while (++i < nb_way)
			{
				j = -1;
				while (map->way[i] != 0 && map->way[i][++j] != -1)
					if (map->way[n][m] == map->way[i][j])
					{
						map->comp[n] = no_comp_realloc(map->comp[n] , i);
						map->comp[i] = no_comp_realloc(map->comp[i] , n);
						break ;
					}
			}
		}
	}
	return (1);
}

void	put_comp(t_map *map)
{
	int n;
	int m;

	n = -1;
	while (++n < map->room[map->start].nb_connection)
	{
		m = -1;
		while (map->comp[n][++m] != -1)
		{
			ft_putnbr(map->comp[n][m]);
			ft_putchar(' ');
		}
		ft_putendl("");
	}
}

void get_all_way(t_map *map)
{
	int n;
	int nb_way;

	nb_way = map->room[map->start].nb_connection;
	map->way = malloc(sizeof(int*) * nb_way);
	n = -1;
	while (++n < nb_way)
	{
		reset_heat(map);
		map->room[map->start].heat = 0;
		map->way[n] = 0;
		//map->way;
		get_way(map, map->room[map->start].connection[n], 1, &(map->way[n]));
		if (map->way[n] != 0)
			put_co(map->way[n], map);
	}
	test_all_way(map);
	put_comp(map);
}

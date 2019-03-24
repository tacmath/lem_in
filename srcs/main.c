/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/21 15:34:46 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/24 15:40:41 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

//void		get_all_way(t_map *map);
int get_multiple_path(t_map *map);

int		*connection_realloc(int *connection, int *nb_co, int new_co)
{
	int n;
	int *tmp;

	n = -1;
	while (++n < *nb_co)
		if (connection[n] == new_co)
			return (connection);
	(*nb_co)++;
	if (!(tmp = malloc(sizeof(int) * (*nb_co))))
		return (0);
	n = -1;
	while (++n < (*nb_co - 1))
		tmp[n] = connection[n];
	tmp[n] = new_co;
	free(connection);
	return (tmp);
}

int		get_connection(t_map *map, char *line, char ***output) //securise
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
	while (ft_strcmp(map->room[++co2].name, &(line[len + 1])) &&
			co2 < map->nb_room)
		;
	if (ft_strncmp(map->room[co1].name, line, len) || ft_strcmp(map->room[co2].name, &(line[len + 1])))
		return (0);
	if (!(map->room[co1].connection =
				connection_realloc(map->room[co1].connection,
					&(map->room[co1].nb_connection), co2)))
		return (0);
	if (!(map->room[co2].connection =
				connection_realloc(map->room[co2].connection,
					(&map->room[co2].nb_connection), co1)))
		return (0);
	return (!add_to_output(output, line) ? 0 : 1);
}

int		get_all_connection(t_map *map, char *line, char ***output)
{
	if (!rooms_init(map))
		return (0);
	if (!get_connection(map, line, output))
		return (0);
	while (get_next_line(0, &line) == 1)
	{
		if (ft_strchr(line, '-') && line[0] != '#')
		{
			if (!get_connection(map, line, output))
				return (0);
		}
		else
			free(line);
	}
	return (1);
}

void	print_room_info(t_map *map)
{
	int n;
	int m;

	n = -1;
	ft_putendl("");
	ft_putendl("");
	ft_putendl("");
	while (++n < map->nb_room)
		ft_putendl(map->room[n].name);
	ft_putendl("");
	n = -1;
	while (++n < map->nb_room)
	{
		m = -1;
		while (map->room[n].connection[++m] != -1)
		{
			ft_putstr(map->room[n].name);
			ft_putstr("-");
			ft_putstr(map->room[map->room[n].connection[m]].name);
			ft_putendl("");
		}
	}
	ft_putendl("");
	ft_putstr("start :   ");
	ft_putnbr(map->start);
	ft_putendl("");
	ft_putstr("end :   ");
	ft_putnbr(map->end);
	ft_putendl("");
	ft_putendl("");
	ft_putendl("heat :");
	n = -1;
	while (++n < map->nb_room)
	{
		ft_putstr(map->room[n].name);
		ft_putstr(" - ");
		ft_putnbr(map->room[n].heat);
		ft_putendl("");
	}
}
/*
void	reset_heat(t_map *map)
{
	int n;

	n = -1;
	while (++n < map->nb_room)
		map->room[n].heat = 0;
}*/
/*
int	test_maps(t_map *map, int room)
{
	int n;
	int co;

//	ft_putendl(map->room[room].name);
	if (room == map->start || room == map->end)
		return (1);
	map->room[room].hype = 1;
	n = -1;
	co = 0;
	while (++n < map->room[room].nb_connection)
	{
		if (map->room[map->room[room].connection[n]].hype != 1)
			if (test_maps(map, map->room[room].connection[n]))
				co++;
	}
	map->room[room].hype = 0;
	if (co != 0)
		return (1);
	n = -1;
	while (++n < map->room[room].nb_connection)
		if (map->room[map->room[room].connection[n]].hype == 1)
			sta_line(map, room, map->room[room].connection[n]);
//	map->room[room].hype = 0;
	return (0);
}
*/
int	test_room(t_map *map, int room)
{
	int n;

	if (room == map->start || room == map->end)
		return (1);
	map->room[room].heat = 1;
	n = -1;
	while (++n < map->room[room].nb_connection)
	{
		if (map->room[map->room[room].connection[n]].heat != 1)
			if (test_room(map, map->room[room].connection[n]))
				return (1);
	}
	return (0);
}

void test_all_maps(t_map *map)
{
//	int n;
	int m;

/*	n = -1;
	while (++n < map->nb_room)
	{
		reset_hype(map);
		map->room[n].hype = 1;*/
		m = -1;
		while (++m < map->room[map->end].nb_connection)
				if (!test_room(map, map->room[map->end].connection[m]))
				{
					sta_line(map, map->end, map->room[map->end].connection[m]);
		//			m = -1;
				}
//	}
}

int		remove_useless_co(t_map *map)
{
	int n;

	n = -1;
	while (++n < map->room[map->start].nb_connection)
		if (map->room[map->room[map->start].connection[n]].heat == -1)
		{
			if (!sta_line(map, map->start, map->room[map->start].connection[n]))
				return (0);
		}
		/*else
			test_maps(map, map->room[map->start].connection[n]);*/
	//	test_all_maps(map);
	return (1);
}

int		main(void)
{
	t_map	*map;
	char	**output;
	int		n;

	output = 0;
	if (!(map = malloc(sizeof(t_map))))
		return (-1);
	if (!init_struct(map, &output))
		return (-1);
	if (!get_room(map, &output))
		return (-1);
	n = -1;
	if (!get_error(map))
	{
		while (output[++n] != 0)
			free(output[n]);
		free(output);
		return (-1);
	}
	write_output(output);
	ft_putchar('\n');
	if (!remove_useless_co(map))
		return (-1);
	get_multiple_path(map);
//	get_all_way(map);
/*	n = -1;
	while (++n < map->nb_ant)
		//while (map->ant[map->nb_ant - 1] != map->end)
		if (map->ant[n] != map->end)
		{
			reset_hype(map);
	//		ft_putendl("!!!!!!!!!!!!!1");
			kylie_jenner(map);
	//		ft_printf("%%%%%%%f\n",map->room[map->end].hype);
	//		ft_putendl("!!!!!!!!!!!!!2");

			move_ant(map);
//			ft_putendl("!!!!!!!!!!!!!3");

			n--;
		}*/
	//print_room_info(map);
	free_map(map);
	return (0);
}

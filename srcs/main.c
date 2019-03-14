/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/21 15:34:46 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/14 13:05:33 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

int		add_to_output(char ***output, char *new_line)
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

char	*get_room_name(char *line, char ***output)
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

int		room_realloc(t_map *map, char *line, char ***output)
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

int		rooms_init(t_map *map)
{
	int n;

	n = -1;
	while (++n < map->nb_room)
	{
		if (!(map->room[n].connection = malloc(sizeof(int))))
			return (0);
		map->room[n].connection[0] = -1;
		map->room[n].heat = -1;
		map->room[n].hype = 0;
		map->room[n].ant = 0;
		map->room[n].nb_connection = 0;
	}
	n = -1;
	while (++n < map->nb_ant)
		map->ant[n] = map->start;
	return (1);
}

int		*connection_realloc(int *connection, int new_co)
{
	int n;
	int *tmp;

	n = -1;
	while (connection[++n] != -1)
		;
	if (!(tmp = malloc(sizeof(int) * (n + 2))))
		return (0);
	n = -1;
	while (connection[++n] != -1)
		tmp[n] = connection[n];
	tmp[n] = new_co;
	tmp[n + 1] = -1;
	free(connection);
	return (tmp);
}

int		get_connection(t_map *map, char *line, char ***output) //securite!!!!!!
	//double connections
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
	if (!(map->room[co1].connection =
				connection_realloc(map->room[co1].connection, co2)))
		return (0);
	if (!(map->room[co2].connection =
				connection_realloc(map->room[co2].connection, co1)))
		return (0);
	(map->room[co1].nb_connection)++;
	(map->room[co2].nb_connection)++;
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
		if (ft_strchr(line, '-'))
		{
			if (!get_connection(map, line, output))
				return (0);
		}
		else
			free(line);
	}
	return (1);
}

int		get_start_and_end(t_map *map, char *line, char ***output)
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

int		get_room(t_map *map, char ***output)
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

void	get_room_heat(t_map *map, int room, int heat)
{
	int	n;
	int	co;

	map->room[room].heat = heat;
	n = -1;
	while (map->room[room].connection[++n] != -1)
	{
		co = map->room[room].connection[n];
		if (map->room[co].heat == -1 || map->room[co].heat > heat + 1)
			get_room_heat(map, co, heat + 1);
	}
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

int		get_error(t_map *map)
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

int		init_struct(t_map *map, char ***output)
{
	char *line;

	if (!(*output = ft_memalloc(sizeof(char*))))
		return (-1);
	if (get_next_line(0, &line) < 1)
		return (0);
	map->nb_ant = ft_atoi(line);
	if (!(add_to_output(output, line)))
		return (0);
	if (map->nb_ant <= 0)
	{
		free(*(output)[0]);
		free(*output);
		free(map);
		ft_putendl("ERROR");
		return (0);
	}
	if (!(map->ant = malloc(sizeof(int) * map->nb_ant)))
		return (ft_super_free(1, map));
	map->room = 0;
	map->start = -1;
	map->end = -1;
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
	print_room_info(map);
	free_map(map);
	return (0);
}

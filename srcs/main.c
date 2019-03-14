/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/21 15:34:46 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/14 16:52:18 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

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

void	reset_hype(t_map *map)
{
	int n;

	n = -1;
	while (++n < map->nb_room)
		map->room[n].hype = 0;
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
	n = -1;
	while (++n < map->nb_ant)
		if (map->ant[n] != map->end)
		{
			reset_hype(map);
			kylie_jenner(map);
			move_ant(map);
			n--;
		}
	//print_room_info(map);
	free_map(map);
	return (0);
}

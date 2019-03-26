/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   resol.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/14 14:26:27 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/26 13:07:04 by lperron     ###    #+. /#+    ###.fr     */
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
	if (!(tmp = malloc(sizeof(int) * (*len + ft_strlen(ant_nb) + 3 + ft_strlen(room_name)))))
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
	free(*line);
	free(ant_nb);
	*line = tmp;
	return (1);
}

/*
void		put_resol(t_map *map, int ant, int room)
{
	ft_putchar('L');
	ft_putnbr(ant + 1);
	ft_putchar('-');
	ft_putstr(map->room[room].name);
	ft_putchar(' ');
}




void	move_ant(t_map	*map)
{
	int		hype_max;
	int		best_room;
	int		i;
	t_room	*room;
	int		ant;

	ant = -1;
	while (++ant < map->nb_ant)
	{
		if (map->ant[ant] != map->end)
		{
		i = -1;
		hype_max = 99999999;
		best_room = -1;
		room = &(map->room[map->ant[ant]]);
//		hype_max = map->room[room->connection[0]].hype + 1;
		while (++i < room->nb_connection)
		{
		//	ft_printf("???????%d\n",i);
			if (map->room[room->connection[i]].hype <
					hype_max && map->room[room->connection[i]].ant == 0 && room->connection[i] != map->last_room[ant])
			{
				best_room = i;
				hype_max = map->room[room->connection[best_room]].hype;
	//			ft_printf("Best room = %s\n", map->room[room->connection[best_room]].name);
			}
	//		ft_printf("%s : %f\n", map->room[room->connection[best_room]].name, map->room[room->connection[best_room]].hype);
	//
		}
		if (best_room != -1)
		{
			put_moving_ant(map, ant, room->connection[best_room]);
			if (room->connection[best_room] != map->end)
				map->room[room->connection[best_room]].ant = 1;
			room->ant = 0;
			map->last_room[ant] = map->ant[ant];
			map->ant[ant] = room->connection[best_room];
		}
	}
	}
	ft_putchar('\n');
}*/

void	push_test_compa(int	*test_compa, int path, int size)
{
	int		i;

	i = -1;
	while (++i < size && test_compa[i] != -1)
		;
	test_compa[i] = path;
}

double	compute_flow(t_map *map, int *test_compa, int size)
{
	int		i;
	double	flow;

	i = -1;
	flow = size;
	if (!test_compa)
		return (0);
	while (++i < size)
	{
		ft_printf("compute : %d\n", i);
		if (test_compa[i] == -1)
			return (0);
		flow /= map->path_len[test_compa[i]];
	}
	ft_printf( _RED_ "flow = %f\n" _EOC_ , flow);
	return (flow);
}

int		recur_get_step(int	*test_compa, int size)
{
	int	i;

	i = -1;
	while (++i < size && test_compa[i] != -1)
		;
	return (i);
}

int		*cpy_path_array(int *src, int size)
{
	int	i;
	int	*dest;

	if (!(dest = malloc(sizeof(int) * size)))
		return (NULL);
	i = -1;
	while (++i < size)
		dest[i] = src[i];
	return (dest);
}

double	fucking_recursive(t_map *map, int **best, int	**test, int size) // for the moment we just compare best to best............
{
	int		i;
	int		ok;
	int		j;

	i = -1;
	ft_printf("TRUXbbbbbbbbbbb\n");
	if (*test && recur_get_step(*test, size) == size)
	{
		if (compute_flow(map, *test,  size) > compute_flow(map, *best, size))
		{
			free(*best);
			*best = cpy_path_array(*test, size); //abort abort (we need to freeeeee)
		}
		return (compute_flow(map, *best, size));
	}
	//allocate test

	if (*test == NULL) //okay it's the first
	{
		ft_printf("alllocattttt  %d\n", size);
		if (!(*test = malloc(sizeof(int) * size)))
			return (-1);
		while (++i < size)
		{
			ft_printf("tt:%d\n", i);
			(*test)[i] = -1;
		}
		ft_printf("tete\n");
		*best = NULL;
	}
	ft_putendl("OK");
	j = -1;
	while (++j < map->nb_path) // we add a path in compa and recur !!!!!!
	{
		i = -1;
		ok = 1;
		ft_printf("ll%d\n", j);
		while(++i < size) //can add this path
		{
			ft_printf("jj i = %d\n", i);
			if ((*test)[i] != -1 && map->path_compat.matrix[*test[i]][j] == 0)
				ok = 0;
		}
		ft_printf("TRUX\n");
		if (ok)
		{
			ft_printf("TRUXiii\n");
			push_test_compa(*test, j, size);
			fucking_recursive(map, best, test, size); 
			/*if (fucking_recursive(map, best, test, size) > compute_flow(map, *best, size))
			{
				free(*best);
				*best = cpy_path_array(*test, size); //abort abort (we need to freeeeee)
			}
			*/
		}
	}
	return (compute_flow(map, *best, size));
}

int		resol(t_map *map)
{
	int		i;
	double	test_flow;
	int		*test_compa;
	int		*tmp;

	i = 0;
	map->best_flow = 0;
	map->best_compa = NULL;
	while (++i < map->nb_ant && i < map->nb_path)
	{
		ft_printf( _RED_ "ant++\n" _EOC_ );
		test_compa = NULL;
		tmp = NULL;
		if (((test_flow = fucking_recursive(map, &test_compa, &tmp, i)) < 0))
			return (0);
		ft_printf( _GREEN_ "test = %f real best = %f \n", test_flow, compute_flow(map, test_compa, i));

		if (map->best_flow > test_flow) //in the recursive, if we can't find a new path, we need to set test_flow to 0;
		{
			free (test_compa);
			break;
		}
		map->best_flow = test_flow;
		if (map->best_compa)
			free(map->best_compa);

		map->best_compa = test_compa;
		map->best_nb_compat = i;
		ft_printf( _BLUE_ "RECUR OK size = %d\n   best_flow = %f\n" _EOC_ , i, map->best_flow);
	}
	ft_printf( _GREEN_ "Byyye\n" _EOC_ );
	return (1);
}

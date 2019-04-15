/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   path.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/06 18:20:24 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/15 16:56:22 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

static int	*add_room_to_path(int *path, int room, int len)
{
	int *new_path;
	int n;

	if (!(new_path = malloc(sizeof(int) * (len + 1))))
		return (0);
	n = -1;
	while (++n < len)
		new_path[n] = path[n];
	new_path[n] = room;
	return (new_path);
}

static void	res_heat(t_map *map)
{
	int n;

	n = -1;
	while (++n < map->nb_room)
		map->room[n].heat = -1;
}
// remove
void draw_all_path(t_map *map, int start)
{
	int n;
	int m;

	n = start - 1;
	while (++n < map->nb_path)
	{
		if (map->path[n][map->path_len[n] - 1] == map->end && map->path_len[n] < map->best_speed)
		{
		m = -1;
		while (++m < map->path_len[n])
		{
			ft_putstr(map->room[map->path[n][m]].name);
			ft_putchar(' ');
		}
		ft_putendl("");
		}
	}
}

static int split_path(t_map *map, int n, int m, int room)
{
	if (map->tmp == 0 && (map->tmp = map->path[n]))
	{
		if (!(map->path[n] = add_room_to_path(map->tmp,
			map->room[room].connection[m], map->path_len[n]++)))
			return (0);
	}
	else
	{
		if (map->nb_path % 1000 == 0 && (!(map->path =
			(int**)ft_realloc((void**)&(map->path),
			sizeof(int*) * map->nb_path, sizeof(int*) *
			(map->nb_path + 1000))) || !(map->path_len =
			(int*)ft_realloc((void**)&(map->path_len),
			sizeof(int) * map->nb_path, sizeof(int)
			* (map->nb_path + 1000)))))
			return (0);
		if (!(map->path[map->nb_path] = add_room_to_path(map->tmp,
			map->room[room].connection[m], map->path_len[n] - 1)))
			return (0);
		map->path_len[map->nb_path++] = map->path_len[n];
	}
	if (map->room[room].connection[m] != map->end &&
		map->room[room].connection[m] != map->start)
		map->room[map->room[room].connection[m]].heat = 1;
	return (1);
}

int	get_all_path(t_map *map, int start_path)
{
	int n;
	int m;
	int room;
	int ret;
	int nb_path;

	ret = 1;
	while (ret && !(ret = 0))
	{
		nb_path = map->nb_path;
		n = start_path - 1;
		while (++n < nb_path && !(map->tmp = 0))
			if ((room = map->path[n][map->path_len[n] - 1])
				!= map->end && room != map->start)
			{
				m = -1;
				while (++m < map->room[room].nb_connection)
					if (
map->room[map->room[room].connection[m]].heat == -1 && (++ret))
						if (!split_path(map, n, m, room))
							return (0);
				free(map->tmp);
			}
	}
	return (1);
}

int path_cmp(int *path1, int *path2, int path_len)
{
	int n;

	n = -1;
	while (++n < path_len)
		if (path1[n] != path2[n])
			return (0);
	return (1);
}

static int init_one_path(t_map *map, int **tmp, int n, int *nb_path)
{
	int m;

	tmp[*nb_path] = map->path[n];
	map->tmp[*nb_path] = map->path_len[n];
	if (!(map->path_room[*nb_path] =
		ft_memalloc(sizeof(uint64_t) * ((map->nb_room >> 6) + 1))))
		return (0);
	m = -1;
	while (tmp[*nb_path][++m] != map->end)
		map->path_room[*nb_path][tmp[*nb_path][m] >> 6] |= 1ULL
		<< (tmp[*nb_path][m] % 64);
	(*nb_path)++;
	return (1);
}

static int path_init(t_map *map, int **tmp, int n)
{
	int nb_path;
	int m;
	int mem;
	
	nb_path = 0;
	while (++n < map->nb_path)
		if (map->path[n][map->path_len[n] - 1] == map->end)
		{
			mem = 0;
			m = n;
			while (++m < map->nb_path)
				if (map->path_len[n] == map->path_len[m] &&
		path_cmp(map->path[n], map->path[m], map->path_len[n]))
					mem = 1;
			if (mem == 0)
			{
				if (!init_one_path(map, tmp, n, &nb_path))
					return (0);
			}
			else
				free(map->path[n]);
		}
		else
			free(map->path[n]);
	return (1);
}

int get_usable_path(t_map *map, int n, int nb_path)
{
	int **tmp;
	int mem;
	int m;

	while (++n < map->nb_path)
		if (map->path[n][map->path_len[n] - 1] == map->end && !(mem = 0))
		{
			m = n;
			while (++m < map->nb_path)
				if (map->path_len[n] == map->path_len[m]
	&& path_cmp(map->path[n], map->path[m], map->path_len[n]))
					mem = 1;
			if (mem == 0)
				nb_path++;
		}
	if (!(tmp = malloc(sizeof(int*) * nb_path )) || !(map->tmp =
malloc(sizeof(int) * nb_path)) || !(map->path_room = malloc(sizeof(uint64_t*) *
nb_path)) || !path_init(map, tmp, -1))
		return (0);
	ft_super_free(2, map->path_len, map->path);
	map->path = tmp;
	map->path_len = map->tmp;
	map->nb_path = nb_path;
	return (1);
}

void sort_path(t_map *map)
{
	int tmp_len;
	uint64_t *tmp_bin;
	int n;
	int m;
	int *tmp;

	m = -1;
	while (++m < map->nb_path)
	{
		n = -1;
		while (++n < map->nb_path - 1)
			if (map->path_len[n] > map->path_len[n + 1])
			{
				tmp_len = map->path_len[n + 1];
				tmp = map->path[n + 1];
				tmp_bin = map->path_room[n + 1];
				map->path[n + 1] = map->path[n];
				map->path_len[n + 1] = map->path_len[n];
				map->path_room[n + 1] = map->path_room[n];
				map->path[n] = tmp;
				map->path_len[n] = tmp_len;
				map->path_room[n] = tmp_bin;
			}
	}
}

void rev_path(t_map *map, int nb_path)
{
	int n;
	int tmp;

	if (map->path[nb_path][map->path_len[nb_path] - 1] == map->start)
	{
		map->path[nb_path][map->path_len[nb_path] - 1] = map->end;
		n = -1;
		while (++n < (map->path_len[nb_path] - 1) / 2)
		{
			tmp = map->path[nb_path][n];
			map->path[nb_path][n] =
			map->path[nb_path][map->path_len[nb_path] - n - 2];
			map->path[nb_path][map->path_len[nb_path] - n - 2] = tmp;
		}
		map->path[nb_path][map->path_len[nb_path] - 1] = map->end;
	}
}

void get_more_path(t_map *map)
{
	int mem[map->max_compa + 1];
	int mem2[map->max_compa + 1];
	int m;
	int n;
	int i;
	int j;
	int nb;

	mem[0] = -1;
	m = -1;
	while (++m < map->nb_path)
	{
		nb = 0;
		if (map->path[m][map->path_len[m] - 1] == map->end)
		{
			n = m;
			while (++n < map->nb_path)
				if (map->path[n][map->path_len[n] - 1] == map->end && map->path[m][map->path_len[m] - 2] == map->path[n][map->path_len[n] - 2])
					nb++;
		}
		if (nb >= 1)
		{
			n = -1;
			while (mem[++n] != -1)
				if (mem[n] == map->path[m][map->path_len[m] - 2])
					break ;
			if (mem[n] == -1)
			{
				mem[n] = map->path[m][map->path_len[m] - 2];
				mem[n + 1] = -1;
			}
		}
	}
	mem2[0] = -1;
	m = -1;
	while (++m < map->nb_path)
	{
		nb = 0;
		if (map->path[m][map->path_len[m] - 1] == map->end)
		{
			n = m;
			while (++n < map->nb_path)
				if (map->path[n][map->path_len[n] - 1] == map->end && map->path[m][0] == map->path[n][0])
					nb++;
		}
		if (nb >= 1)
		{
			n = -1;
			while (mem2[++n] != -1)
				if (mem2[n] == map->path[m][0])
					break ;
			if (mem2[n] == -1)
			{
				mem2[n] = map->path[m][0];
				mem2[n + 1] = -1;
			}
		}
	}
	res_heat(map);
	n = -1;
	while (mem[++n] != -1)
		map->room[mem[n]].heat = 1;
	n = -1;
	j = 0;
	map->path = (int**)ft_realloc((void**)&(map->path), sizeof(int*) * map->nb_path, sizeof(int*) * (map->nb_path + 1000));
	map->path_len = (int*)ft_realloc((void**)&(map->path_len), sizeof(int) * map->nb_path, sizeof(int) * (map->nb_path + 1000));
	m = map->nb_path;
	while (++n < map->room[map->end].nb_connection)
	{
		i = -1;
		while (mem2[++i] != -1)
			if (mem2[i] == map->room[map->start].connection[n])
				break ;
		if (mem2[n] == -1)
		{
			map->path[m + n - j] = malloc(sizeof(int));
			map->path[m + n - j][0] = map->room[map->start].connection[n];
			map->nb_path++;
			map->path_len[m + n - j] = 1;
			map->room[map->start].heat = 1;
			map->room[map->room[map->start].connection[n]].heat = 1;
		}
		else
		{
			map->room[map->room[map->start].connection[n]].heat = 1;
			j++;
		}
	}
	get_all_path(map, m);
}

int get_last_path(t_map *map)
{
	int n;
	int m;
	int start_path;
	
	res_heat(map);
	n = -1;
	while (map->best_compa[++n] != -1)
	{
		m = -1;
		while (++m < map->path_len[map->best_compa[n]] - 1)
			 map->room[map->path[map->best_compa[n]][m]].heat = 1;
	}
	n = -1;
	map->path = (int**)ft_realloc((void**)&(map->path), sizeof(int*) * map->nb_path, sizeof(int*) * (map->nb_path + 1000));
	map->path_len = (int*)ft_realloc((void**)&(map->path_len), sizeof(int) * map->nb_path, sizeof(int) * (map->nb_path + 1000));
	start_path = map->nb_path;
	m = 0;
	while (++n < map->room[map->start].nb_connection)
	{
		if (map->room[map->room[map->start].connection[n]].heat == -1)
		{
			map->path[start_path + n - m] = malloc(sizeof(int));
			map->path[start_path + n - m][0] = map->room[map->start].connection[n];
			map->nb_path++;
			map->path_len[start_path + n - m] = 1;
			map->room[map->start].heat = 1;
			map->room[map->room[map->start].connection[n]].heat = 1;
		}
		else
			m++;
	}
	get_all_path(map, start_path);
	draw_all_path(map, start_path);
	return (1);
}

int get_multiple_path(t_map *map)
{
	int n;
	int start_path;
	int start_of_rev;
//	int	count;

	n = -1;
	map->nb_path = 0;
	res_heat(map);
	map->path = malloc(sizeof(int*) * 1000);
	map->path_len = malloc(sizeof(int) * 1000);
	start_path = map->nb_path;

	while (++n < map->room[map->start].nb_connection)
	{
		map->path[start_path + n] = malloc(sizeof(int));
		map->path[start_path + n][0] = map->room[map->start].connection[n];
		map->nb_path++;
		map->path_len[start_path + n] = 1;
		map->room[map->start].heat = 1;
		map->room[map->room[map->start].connection[n]].heat = 1;
	}
	get_all_path(map, start_path);
	start_of_rev = map->nb_path;
	n = -1;
	res_heat(map);	
	map->path = (int**)ft_realloc((void**)&(map->path), sizeof(int*) * map->nb_path, sizeof(int*) * (map->nb_path + 1000));
	map->path_len = (int*)ft_realloc((void**)&(map->path_len), sizeof(int) * map->nb_path, sizeof(int) * (map->nb_path + 1000));
	start_path = map->nb_path;
	while (++n < map->room[map->end].nb_connection)
	{
		map->path[start_path + n] = malloc(sizeof(int));
		map->path[start_path + n][0] = map->room[map->end].connection[n];
		map->nb_path++;
		map->path_len[start_path + n] = 1;
		map->room[map->end].heat = 1;
		map->room[map->room[map->end].connection[n]].heat = 1;
	}
	get_all_path(map, start_path);
	//    ft_putnbr(map->nb_path);
	//    ft_putendl("");
	n = start_of_rev - 1;
	while (++n < map->nb_path)
		rev_path(map, n);
	map->max_compa = ft_min(map->room[map->start].nb_connection, map->room[map->end].nb_connection);
	//get_more_path(map);
	//get_more_path(map);
	//get_more_path(map);
	//get_more_path(map);

	//	draw_all_path(map);
	if (!get_usable_path(map, -1, 0))
		return (0);
	sort_path(map);
	//draw_all_path(map);
	if (!compatibility_all(map))
		return (0);
//	get_best_path_comp(map);

	resol(map);
	printf_best_compa(map);
	get_last_path(map);
//	draw_all_path(map);
	//
	/*for (int i= 0; i < map->nb_path; i++)
	  {
	  ft_putstr("( ");
	  for (int j = 0; j < map->nb_path; j++)
	  ft_printf("%d ", (int)map->path_compat.matrix[i][j]);
	  ft_putendl(")");
	  }*/
	//ft_printf("path %d : %d\n", i, map->path_compat.nb_compat[i]);
	//
		ft_putnbr(map->nb_path);
		ft_putendl("");
	//	ft_putendl("NOW!");
	//	resol(map);
	//	for (int i = 0; i< map->best_nb_compat; i++)
	//		ft_printf("%d ", map->best_compa[i]);
	//	ft_putendl("");
	//	draw_all_path(map);
//	count = 0;
//	gogogo(map, &count);
	return (1);
}


// make an other function

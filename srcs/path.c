
#include "lem_in.h"

int *add_room_to_path(int *path, int room, int len)
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

void res_heat(t_map *map)
{
	int n;

	n = -1;
	while (++n < map->nb_room)
		map->room[n].heat = -1;


}

void draw_all_path(t_map *map)
{
	int n;
	int m;

	n = -1;
	while (++n < map->nb_path)
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

int get_all_path(t_map *map, int start_path)
{
	int n;
	int m;
	int room;
	int ret;
	int *tmp;
	int nb_path;

	while (1)
	{
		ret = 0;
		nb_path = map->nb_path;
		n = start_path - 1;
		while (++n < nb_path)
		{
			room = map->path[n][map->path_len[n] - 1];
			if (room != map->end)
			{
				tmp = 0;
				m = -1;
				while (++m < map->room[room].nb_connection)
					if (map->room[map->room[room].connection[m]].heat == -1)
					{
						if (tmp == 0)
						{
							tmp = map->path[n];
							map->path[n] = add_room_to_path(tmp, map->room[room].connection[m], map->path_len[n]);
							map->path_len[n]++;
						}
						else
						{
							if (map->nb_path % 1000 == 0)
							{
								map->path = (int**)ft_realloc((void**)&(map->path), sizeof(int*) * map->nb_path, sizeof(int*) * (map->nb_path + 1000));
								map->path_len = (int*)ft_realloc((void**)&(map->path_len), sizeof(int) * map->nb_path, sizeof(int) * (map->nb_path + 1000));
							}
							map->path[map->nb_path] = add_room_to_path(tmp, map->room[room].connection[m], map->path_len[n] - 1);
							map->path_len[map->nb_path] = map->path_len[n];
							map->nb_path++;
						}
						if (map->room[room].connection[m] != map->end)
							map->room[map->room[room].connection[m]].heat = 1;
						ret++;
					}
				free(tmp);
			}
		}
		if (ret == 0)
			break ;
	}
	return (1);
}

int get_usable_path(t_map *map)
{
	int **tmp;
	int *tmp_len;
	int nb_path;
	int n;
	int m;
	
	n = -1;
	nb_path = 0;
	while (++n < map->nb_path)
		if (map->path[n][map->path_len[n] - 1] == map->end)
			nb_path++;
	if (!(tmp = malloc(sizeof(int*) * nb_path)))
		return (0);
	if (!(tmp_len = malloc(sizeof(int) * nb_path)))
		return (0);
	if (!(map->path_room = malloc(sizeof(uint64_t*) * nb_path)))
		return (0);
	n = -1;
	nb_path = 0;
	while (++n < map->nb_path)
		if (map->path[n][map->path_len[n] - 1] == map->end)
		{
			tmp[nb_path] = map->path[n];
			tmp_len[nb_path] = map->path_len[n];
			if (!(map->path_room[nb_path] = ft_memalloc(sizeof(uint64_t) * ((map->nb_room >> 6) + 1))))
				return (0);

			m = -1;
			while (tmp[nb_path][++m] != map->end)
				map->path_room[nb_path][tmp[nb_path][m] >> 6] |= 1 << tmp[nb_path][m] % 64;
			nb_path++;
		}
		else
			free(map->path[n]);
	free(map->path);
	free(map->path_len);
	map->path = tmp;
	map->path_len = tmp_len;
	map->nb_path = nb_path;
	return (1);
}

void sort_path(t_map *map)
{
	int tmp_len;
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
				map->path[n + 1] = map->path[n];
				map->path_len[n + 1] = map->path_len[n];
				map->path[n] = tmp;
				map->path_len[n] = tmp_len;			
			}
	}
}

int get_multiple_path(t_map *map)
{
	int n;
	int start_path;

	n = -1;
	map->nb_path = 0;
	while (++n < map->room[map->start].nb_connection)
	{
		start_path = map->nb_path;
 		res_heat(map);
		if (map->nb_path != 0) 
		{
			map->path = (int**)ft_realloc((void**)&(map->path), sizeof(int*) * map->nb_path, sizeof(int*) * (map->nb_path + 1000));
			map->path_len = (int*)ft_realloc((void**)&(map->path_len), sizeof(int) * map->nb_path, sizeof(int) * (map->nb_path + 1000));
		}
		else
		{
			map->path = malloc(sizeof(int*) * 1000);
			map->path_len = malloc(sizeof(int) * 1000);
		}
		map->path[start_path] = malloc(sizeof(int));
		map->path[start_path][0] = map->room[map->start].connection[n];
		map->nb_path++;
		map->path_len[start_path] = 1;
		map->room[map->start].heat = 1;
		map->room[map->room[map->start].connection[n]].heat = 1;
		get_all_path(map, start_path);
	}
	get_usable_path(map);
	sort_path(map);
	if (!compatibility_all(map))
		return (0);
	//
/*	for (int i= 0; i < map->nb_path; i++)
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
//	draw_all_path(map);
	return (1);
}


// make an other function

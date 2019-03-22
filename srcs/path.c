
#include "lem_in.h"

int *add_room_to_path(int *path, int room, int len)
{
	int *new_path;
	int n;

	if (!(new_path = malloc(sizeof(int) * (len + 1))))
		return (0);
	n = -1;
	while (++n < len)
	{
		new_path[n] = path[n];
	//	ft_putnbr(path[n]);
	//	ft_putchar(' ');
	}
	new_path[n] = room;
//	ft_putnbr(room);
//	ft_putendl("");
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

	//init room somewhere

//	res_heat(map);	
//	map->path = malloc(sizeof(int*) /* 100000*/);
//	map->path[0] = malloc(sizeof(int));
//	map->path[0][0] = map->start;
//	map->path_len = malloc(sizeof(int) /* 100000*/);
//	map->path_len[0] = 1;
//	map->nb_path = 1;
//	map->room[map->start].heat = 1;
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
	//			ft_putendl("ok");

				while (++m < map->room[room].nb_connection)
					if (map->room[map->room[room].connection[m]].heat == -1)
					{
						if (tmp == 0)
						{
	//									ft_putendl("okkkkkkkkkkkk");

							tmp = map->path[n];
							map->path[n] = add_room_to_path(tmp, map->room[room].connection[m], map->path_len[n]);
							map->path_len[n]++;
	//							ft_putendl("ooooooooooooooooook");

						}
						else
						{
							map->path = (int**)ft_realloc((void**)&(map->path), sizeof(int*) * map->nb_path, sizeof(int*) * (map->nb_path + 1));
							map->path_len = (int*)ft_realloc((void**)&(map->path_len), sizeof(int) * map->nb_path, sizeof(int) * (map->nb_path + 1));
							map->path[map->nb_path] = add_room_to_path(tmp, map->room[room].connection[m], map->path_len[n] - 1);
							//map->nb_path++;				//realloc or huge buffer
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
//	draw_all_path(map);
	return (1);
}

int get_multiple_path(t_map *map)
{
	int n;
	int start_path;

	n = -1;
	map->nb_path = 0;
	//map->path = 0;
	//map->path_len = 0;
	while (++n < map->room[map->start].nb_connection)
	{
		start_path = map->nb_path;
 		res_heat(map);
		//map->path = malloc(sizeof(int*) /* 100000*/);
		if (map->nb_path != 0) 
		{
			map->path = (int**)ft_realloc((void**)&(map->path), sizeof(int*) * map->nb_path, sizeof(int*) * (map->nb_path + 1));
			map->path_len = (int*)ft_realloc((void**)&(map->path_len), sizeof(int) * map->nb_path, sizeof(int) * (map->nb_path + 1));
		}
		else
		{
			map->path = malloc(sizeof(int*) /* 100000*/);
			map->path_len = malloc(sizeof(int) /* 100000*/);
		}
		map->path[start_path] = malloc(sizeof(int));
		map->path[start_path][0] = map->room[map->start].connection[n];
		//map->path_len = malloc(sizeof(int) /* 100000*/);
		map->nb_path++;
		map->path_len[start_path] = 1;
		map->room[map->start].heat = 1;
		map->room[map->room[map->start].connection[n]].heat = 1;
		get_all_path(map, start_path);
	}
	ft_putnbr(map->nb_path);
//	draw_all_path(map);
	return (1);
}


// make an other function

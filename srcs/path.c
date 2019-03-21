
#include "lem_in.h"

int *add_room_to_path(int *path, int room, int len)
{
	int *new_path;
	int n;

	if (!(new_path = malloc(sizeof(int) * len + 1)))
		return (0);
	n = -1;
	while (++n < len)
		new_path[n] = path[n];
	new_path[n] = room;
	return (new_path);
}

int get_all_path(t_map *map, int room)
{
	int n;
	int m;
	int ret;
	int *tmp;
	int nb_path;

	//init room somewhere

	while (1)
	{
		ret = 0;
		nb_path = map->nb_path;
		n = -1;
		while (++n < nb_path)
		{
			room = map->path[map->path_len[n] - 1];
			if (room != map->end)
			{
				tmp = 0;
				m = -1;
				while (++m < map->room[room].nb_connection)
					if (map->room[map->room[room].connection[m]].heat != -1)
					{
						if (tmp == 0)
						{
							tmp = map->path[n];
							map->path[n] = add_room_to_path(tmp, map->room[room].connection[m], map->path_len[n]);
							map->path_len[n]++;
						}
						else
						{
							map->path[map->nb_path] = add_room_to_path(tmp, map->room[room].connection[m], map->path_len[n] - 1);
							map->nb_path++;				//realloc or huge buffer
							map->path_len[map->nb_path] = map->path_len[n];
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
}


// make an other function

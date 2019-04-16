/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   path.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/06 18:20:24 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/16 14:33:33 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

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
		ft_putnbr(map->path_len[n]);
		ft_putendl("");
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

int         get_way(t_map *map, int room, int heat, int **way)
{
    int    n;
    int    co;
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
        if (map->room[co].heat == -1 || (map->room[co].heat > heat + 1 && map->room[co].heat != 1) )
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

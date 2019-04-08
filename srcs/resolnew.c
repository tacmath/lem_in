/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   resolnew.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 18:09:19 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/08 02:24:13 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

int		how_long_will_it_beb(t_map *map, int mpath, int best, int *path)
{
	int	n;
	int	lef;
	int	bn;
	int	incr;

	lef = map->nb_ant;
	incr = 0;
	n = 0;
	while (lef > 0 && n < best)
	{
		bn = n;
		n = incr <= mpath ? map->path_len[path[incr]] : n;
		if (incr <= mpath && (n - bn) * incr <= lef)
		{
			lef -= bn == 0 ? incr : (n - bn) * incr;
			while (incr <= mpath && map->path_len[path[incr]] == n && ++incr)
				lef--;
		}
		else
			return (n + lef / incr + 1);
	}
	return (n);
}

int			recur_get_step(int *test_compa, int size)
{
	int	i;

	i = -1;
	while (++i < size && test_compa[i] != -1)
		;
	return (i);
}

void		add_path(uint64_t **megapath, int whereami, uint64_t *new_path,
		int size)
{
	int			i;

	i = -1;
	size = (size >> 6) + 1;
	while (++i < size)
		megapath[whereami + 1][i] = megapath[whereami][i] & new_path[i];
}

int			fucking_recursive(t_map *map, int j, uint64_t **mega, int *comp)
{
	int			speed;
	int			i;
	int			st;

	st = recur_get_step(comp, map->max_compa);
	while (++j < map->nb_path && map->path_len[j] < map->best_speed && st < 999)
		if ((mega[st][j >> 6] & (1ULL << (j % 64))) > 0)
		{
			comp[st] = j;
			add_path(mega, st, map->path_compat.matrixbin[j], map->nb_path);
			if (map->best_speed > (speed = how_long_will_it_beb(map,
							st, map->best_speed, comp)))
			{
				i = -1;
				while (comp[++i] != -1)
					map->best_compa[i] = comp[i];
				map->best_speed = speed;
			}
			(fucking_recursive(map, j, mega, comp));
		}
	if ((st = recur_get_step(comp, map->max_compa)))
		comp[st - 1] = -1;
	return (1);
}

int			resol(t_map *map)
{
	uint64_t	**megapath;
	int			*test_comp;
	int			i;

	if (!(test_comp = malloc(sizeof(int) * (map->max_compa + 1))))
		return (0);
	if (!(map->best_compa = malloc(sizeof(int) * (map->max_compa + 1))))
		return (ft_super_free(1, test_comp));
	if (!(megapath = bin_init(map->nb_path)))
		return (ft_super_free(2, test_comp, map->best_compa));
	i = -1;
	map->best_speed = INT_MAX;
	while (++i < map->max_compa + 1)
	{
		test_comp[i] = -1;
		map->best_compa[i] = -1;
	}
	fucking_recursive(map, -1, megapath, test_comp);
	i = -1;
	while (++i < 1000)
		free(megapath[i]);
	ft_super_free(2, test_comp, megapath);
	return (1);
}

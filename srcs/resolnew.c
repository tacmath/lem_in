/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   resolnew.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 18:09:19 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/15 14:15:13 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

int			how_long_will_it_beb(t_map *map, int mpath, int best, int *path)
{
	int	n;
	int	lef;
	int	bn;
	int	incr;
	int	tmp;

	lef = map->nb_ant;
	incr = 0;
	n = 0;
	while (lef > 0 && n < best)
	{
		bn = n;
		n = incr <= mpath ? map->path_len[path[incr]] : n;
	//	n = incr == 0 ? n - 1 : n;
		if (incr <= mpath && (tmp = (n - bn) * incr) <= lef)
		{
			lef -= bn == 0 ? incr : tmp;
			while (incr <= mpath && map->path_len[path[incr]] == n && ++incr)
				lef--;
		}
		else
			return (n + (lef - 1) / incr + 1);
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
	int			up;

	up = ++(map->recur_step);
//	if ((up == 1 && j >= 5))
//		return (1);
	while (++j < map->nb_path && map->path_len[j] < map->best_speed && map->recur_step < 999)
		if ((mega[map->recur_step][j >> 6] & (1ULL << (j % 64))) > 0)
		{
			comp[map->recur_step] = j;
			add_path(mega, map->recur_step, map->path_compat.matrixbin[j], map->nb_path);
			if (map->best_speed > (speed = how_long_will_it_beb(map,
							map->recur_step, map->best_speed, comp)))
			{
				i = -1;
				while (comp[++i] != -1)
					map->best_compa[i] = comp[i];
				map->best_speed = speed;
			}
			up = 0;
			(fucking_recursive(map, j, mega, comp));
		}
	comp[(up == 0 ? map->recur_step + 1 : map->recur_step) - 1] = -1;
	--(map->recur_step);
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
	map->recur_step = -1;
	fucking_recursive(map, -1, megapath, test_comp);
	i = -1;
	while (++i < 1000)
		free(megapath[i]);
	ft_super_free(2, test_comp, megapath);
	return (1);
}

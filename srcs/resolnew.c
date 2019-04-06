/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   resolnew.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 18:09:19 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/06 17:10:20 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

int			recur_get_step(int *test_compa, int size)
{
	int	i;

	i = -1;
	while (++i < size && test_compa[i] != -1)
		;
	return (i);
}

void		add_path(uint64_t *megapath, uint64_t *new_path, int size)
{
	int			i;

	i = -1;
	size = (size >> 6) + 1;
	while (++i < size)
		megapath[i] &= new_path[i];
}

void		reset_megapath(uint64_t *megapath, int *test_comp, t_map *map,
		int whereami)
{
	int	i;
	int	size;

	size = (map->nb_path >> 6) + 1;
	i = -1;
	while (++i < size)
		megapath[i] = 0xFFFFFFFFFFFFFFFF;
	i = -1;
	while (++i < whereami)
		add_path(megapath,
				map->path_compat.matrixbin[test_comp[i]], map->nb_path);
}

int			fucking_recursive(t_map *map, int j, uint64_t *megapath, int *comp)
{
	int			speed;
	int			i;
	int			whereami;

	whereami = recur_get_step(comp, map->max_compa);
	while (++j < map->nb_path && map->path_len[j] < map->best_speed)
		if ((megapath[j >> 6] & (1ULL << (j % 64))) > 0)
		{
			comp[whereami] = j;
			add_path(megapath, map->path_compat.matrixbin[j], map->nb_path);
			if (map->best_speed > (speed = how_long_will_it_be(map,
							whereami, 0, comp)))
			{
				i = -1;
				while (comp[++i] != -1)
					map->best_compa[i] = comp[i];
				map->best_speed = speed;
			}
			(fucking_recursive(map, j, megapath, comp));
			reset_megapath(megapath, comp, map, whereami);
		}
	if ((whereami = recur_get_step(comp, map->max_compa)))
		comp[whereami - 1] = -1;
	return (1);
}

int			resol(t_map *map)
{
	uint64_t	*megapath;
	int			*test_comp;
	int			i;

	if (!(megapath = bin_init(map->nb_path)))
		return (0);
	if (!(test_comp = malloc(sizeof(int) * (map->max_compa + 1))))
		return (ft_super_free(1, megapath));
	if (!(map->best_compa = malloc(sizeof(int) * (map->max_compa + 1))))
		return (ft_super_free(2, test_comp, megapath));
	i = -1;
	map->best_speed = INT_MAX;
	while (++i < map->max_compa + 1)
	{
		test_comp[i] = -1;
		map->best_compa[i] = -1;
	}
	fucking_recursive(map, -1, megapath, test_comp);
	ft_super_free(2, test_comp, megapath);
	return (1);
}

/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/21 15:34:46 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 16:03:42 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

int		free_output(char **output)
{
	int n;

	if (!output)
		return (0);
	n = -1;
	while (output[++n] != 0)
		free(output[n]);
	free(output);
	return (0);
}

int		main(int ac, char **av)
{
	t_map	*map;
	char	**output;
	int		n;

	output = 0;
	map = 0;
	if (!(map = malloc(sizeof(t_map))) || !init_struct(map, &output)
			|| !get_room(map, &output))
		return (ft_printf("ERROR\n") && !free_output(output) && !free_map(map));
	n = 0;
	while (++n < ac)
		if (av[n][0] == '-' && av[n][1] == 'c' && av[n][2] == '\0')
			map->correction = 1;
	if (!get_error(map))
		return (ft_printf("ERROR\n") && !free_output(output) && !free_map(map));
	write_output(map, output);
	if (!get_multiple_path(map) || !gogogo(map))
		return (!free_map(map));
	return (free_map(map));
}

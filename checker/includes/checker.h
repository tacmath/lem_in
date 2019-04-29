/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   checker.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/21 14:09:06 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/29 14:17:01 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H
# include "libft.h"
# include <stdlib.h>

struct					s_room
{
	int					*connection;
	int					nb_connection;
	char				*name;
	int					ant;
};

typedef struct s_room	t_room;

struct					s_map
{
	t_room				*room;
	int					*ant;
	int					nb_room;
	int					nb_ant;
	int					start;
	int					end;
};

typedef struct s_map	t_map;

int						get_room(t_map *map);
int						rooms_init(t_map *map);
int						get_all_connection(t_map *map, char *line);
int						init_struct(t_map *map);
int						free_map(t_map *map);
int						isroom(char *line);
int						check(t_map *map);

#endif

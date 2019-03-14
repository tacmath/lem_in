/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lem_in.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/21 14:09:06 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/14 13:51:13 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include <stdlib.h>

struct					s_room
{
	int					*connection;
	int					nb_connection;
	char				*name;
	float				hype;
	int					heat;
	char				ant;
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

#endif

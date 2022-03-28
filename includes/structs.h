/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:48:02 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/28 15:49:23 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
#define STRUCTS_H

#include <unistd.h>

typedef struct	s_type
{
	int		id;
	char	*data;
}	t_type;

typedef struct	s_map
{
	t_type	**types;
	char	**map;
	int		nbtypes;
	int		w;
	int		h;
}	t_map;

typedef struct s_prog
{
	void		*mlx;
	void		*win;
	int			w_size;
	t_map		*map;
}	t_prog;

#endif

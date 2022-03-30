/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbel-bas <mbel-bas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:48:02 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/29 18:34:56 by mbel-bas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
#define STRUCTS_H

#include <unistd.h>

# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define F 4
# define C 5

typedef struct	s_type
{
	int		id;
	char	*data;
}	t_type;

typedef struct	s_player
{
	int	x;
	int	y;
}	t_player;

typedef struct s_draw
{
	int		x0;
	int		x1;
	int		y0;
	int		y1;
	int		dy;
	int		dx;
	int		index;
	int		next;
	int		i;
	int		j;
}	t_draw;

typedef struct	s_map
{
	t_type	**types;
	char	**map;
}	t_map;

typedef struct s_prog
{
	void		*mlx;
	void		*win;
	int			w_size;
	t_map		*map;
}	t_prog;

#endif

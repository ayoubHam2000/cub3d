/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:48:02 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/30 11:40:12 by aben-ham         ###   ########.fr       */
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

typedef struct	s_map
{
	t_type	**types;
	char	**map;
	int		w_max;
}	t_map;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct	s_player
{
	float	x;
	float	y;
	float	speed;
	float	angle;
}	t_player;

typedef struct s_prog
{
	void		*mlx;
	void		*win;
	int			w_size;
	t_map		*map;
	t_data		img;
	t_player	player;
}	t_prog;

#endif

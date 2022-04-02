/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbel-bas <mbel-bas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:48:02 by aben-ham          #+#    #+#             */
/*   Updated: 2022/04/02 09:10:26 by aben-ham         ###   ########.fr       */
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
	int		len;
}	t_map;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		img_w;
	int		img_h;
}	t_data;

typedef struct	s_player
{
	float	x;
	float	y;
	int		map_x;
	int		map_y;
	float	speed;
	float	angle;
	float	cos;
	float	sin;
	float	angle_speed;
	float	view_angle;
	float	view_range;
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

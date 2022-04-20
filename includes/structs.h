/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:48:02 by aben-ham          #+#    #+#             */
/*   Updated: 2022/04/04 18:27:21 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
#define STRUCTS_H

#include <unistd.h>

# define TEX_NBR 4
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

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		img_w;
	int		img_h;
}	t_data;

typedef struct s_tex
{
	void	*tex;
	char	*ptr;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}	t_tex;

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
	int		mposx;
}	t_player;

typedef struct s_prog
{
	void		*mlx;
	void		*win;
	int			w_size;
	int			color;
	t_map		*map;
	t_data		img;
	t_player	player;
	t_tex		*texs[TEX_NBR];
}	t_prog;

#endif

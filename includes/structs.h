/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbel-bas <mbel-bas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:48:02 by aben-ham          #+#    #+#             */
/*   Updated: 2022/05/14 15:56:48 by aben-ham         ###   ########.fr       */
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

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_pointf
{
	double	x;
	double	y;
}	t_pointf;

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
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_prog
{
	void		*mlx;
	void		*win;
	t_map		*map;
	t_tex		*texs[TEX_NBR];
	t_player	player;
	int			color;
	int			time;
	int			old_time;
	t_data		img;
	int			pressed_key[2];
	int			m_x;
	int			m_y;
	int			old_m_x;
	int			old_m_y;
}	t_prog;

typedef struct	s_ray
{
	double	x;
	double	y;
	double	pos_x;
	double	pos_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	double	dist;
	double	wall_x;
	int		side;
	int		line_height;
}	t_ray;

#endif

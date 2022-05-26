/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 11:35:58 by aben-ham          #+#    #+#             */
/*   Updated: 2022/05/26 18:11:53 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

static int	max(int a, int b)
{
	if (a < b)
		return (b);
	return (a);
}

static void	init_minimap(t_prog *prog, t_mini_map *m)
{
	m->map = prog->player.map;
	m->map_width = prog->player.map_longest_len * TILE_SIZE_MAP;
	m->map_height = prog->player.map_len * TILE_SIZE_MAP;
	m->p_x = prog->player.x * TILE_SIZE_MAP;
	m->p_y = prog->player.y * TILE_SIZE_MAP;
	m->x_start = max(0, min(m->p_x - MINIMAP_W / 2, m->map_width - MINIMAP_W));
	m->x_end = min(m->map_width, m->x_start + MINIMAP_W);
	m->y_start = max(0, min(m->p_y - MINIMAP_H / 2, m->map_height - MINIMAP_H));
	m->y_end = min(m->map_height, m->y_start + MINIMAP_H);
	m->shift_x = (TILE_SIZE_MAP * 0.5) + WIDTH - m->x_end - 5;
	m->shift_y = (TILE_SIZE_MAP * 0.5) + HEIGHT - m->y_end - 5;
	m->player_map_x = prog->player.x;
	m->player_map_y = prog->player.y;
}

static void	draw_dir(float angle, float length, t_mini_map *m, float color)
{
	float	r;
	float	x;
	float	y;
	int		offset_x;
	int		offset_y;

	offset_x = (m->player_map_x + 0.5) * TILE_SIZE_MAP + m->shift_x;
	offset_y = (m->player_map_y + 0.5) * TILE_SIZE_MAP + m->shift_y;
	r = 0.f;
	length = fmin(length, MAX_LINE);
	while (r < length)
	{
		x = r * cosf(angle);
		y = r * sinf(angle);
		ft_put_pixel(x + offset_x, y + offset_y, color);
		ft_put_pixel(x + offset_x, y + offset_y + 1, color);
		ft_put_pixel(x + offset_x + 1, y + offset_y, color);
		ft_put_pixel(x + offset_x + 1, y + offset_y + 1, color);
		r += 0.1f;
	}
}

void	draw_minimap(t_prog *prog)
{
	t_mini_map	m;
	int			x;
	int			y;

	init_minimap(prog, &m);
	y = m.y_start - 1;
	while (++y < m.y_end)
	{
		x = m.x_start - 1;
		while (++x < m.x_end)
		{
			m.map_x = x / TILE_SIZE_MAP;
			m.map_y = y / TILE_SIZE_MAP;
			if (m.map_x >= ft_strlen(m.map[m.map_y]))
				continue ;
			if (m.map[m.map_y][m.map_x] == '1')
				ft_put_pixel(x + m.shift_x, y + m.shift_y, 0xffffff);
			else if (ft_in(m.map[m.map_y][m.map_x], "WSEN0"))
			{
				ft_put_pixel_in(x + m.shift_x, y + m.shift_y, 100 << 24);
			}
			if (m.map_x == m.player_map_x && m.map_y == m.player_map_y)
				ft_put_pixel(x + m.shift_x, y + m.shift_y, 0xffd700);
			if (prog->player.map_info[m.map_y][m.map_x].type == 'S')
				ft_put_pixel(x + m.shift_x, y + m.shift_y, 0x0000ff);
		}
	}
	draw_dir(atan2(prog->player.dir_y, prog->player.dir_x), 20, &m, 0xffd700);
}

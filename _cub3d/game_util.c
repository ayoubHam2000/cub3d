/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 11:35:13 by aben-ham          #+#    #+#             */
/*   Updated: 2022/05/14 13:41:12 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//////////////
size_t	get_time(void)
{
	static size_t	s;
	struct timeval	t;

	gettimeofday(&t, NULL);
	if (s == 0)
		s = t.tv_sec * 1000000 + t.tv_usec;
	return (t.tv_sec * 1000000 + t.tv_usec - s);
}
//////////////

void	draw_player_in_map()
{
	t_player	*p;

	p = &(get_prog()->player);
	draw_square(TILE_SIZE_MAP * p->x - 1, TILE_SIZE_MAP * p->y - 1, 4, 0xffff00);
	draw_line(atan2(p->dir_y, p->dir_x), 30, p->x * TILE_SIZE_MAP, p->y * TILE_SIZE_MAP, 0xffffff);
}

void	draw_map_world(void)
{
	char	**map;
	int		x;
	int		y;
	int		size;

	map = get_prog()->map->map;
	size = TILE_SIZE_MAP;
	x = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (map[x][y] == '1')
				draw_square(y * size, x * size, size, 0xffffff);
			else
				draw_square(y * size, x * size, size, 0x223322);
			y++;
		}
		x++;
	}
}

void	mini_map(t_prog *prog)
{
	t_point	size;
	
	size.x = get_longest_line_width(prog->map->map) * TILE_SIZE_MAP;
	size.y = prog->map->len * TILE_SIZE_MAP;
	replace_image(prog, HEIGHT, HEIGHT);
	draw_map_world();
	draw_player_in_map();
	mlx_put_image_to_window(prog->mlx, prog->win, prog->img.img, WIDTH, 0);
}

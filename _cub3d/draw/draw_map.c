/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:30:00 by aben-ham          #+#    #+#             */
/*   Updated: 2022/05/19 15:27:48 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_map(void)
{
	char	**map;
	int		x;
	int		y;
	int		size;

	map = get_prog()->player.map;
	size = TILE_SIZE_MAP;
	x = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (get_key_type(map[x][y]) == 'W')
				draw_square(y * size, x * size, size, 0xffffff);
			else
				draw_square(y * size, x * size, size, 0x223322);
			y++;
		}
		x++;
	}
}

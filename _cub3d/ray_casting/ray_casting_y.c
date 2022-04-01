/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_y.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:16:17 by aben-ham          #+#    #+#             */
/*   Updated: 2022/04/01 17:19:23 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static float	ray_on_y(t_player *player, int y)
{
	float	len_y;

	if (player->sin > 0)
		len_y = (player->map_y + 1 + y)	* TILE_SIZE - player->y;
	else if (player->sin < 0)
		len_y = player->y - (player->map_y - y) * TILE_SIZE;
	else
		return (INF);
	return (fabs(len_y / player->sin));
}

static int	is_hit_a_tile_y(t_player *player, float length)
{
	int	x;
	int y;

	x = (player->x + length * player->cos) / TILE_SIZE;
	y = (player->y + length * player->sin) / TILE_SIZE;
	if (player->sin < 0)
		y--;
	return (is_tile(get_prog()->map, x, y));
}

float	ray_casting_y(t_player *player)
{
	float	y;
	float	length;

	y = 0;
	while (y < RAY_LEN)
	{
		length = ray_on_y(player, y);
		if (is_hit_a_tile_y(player, length))
			return (length);
		y++;
	}
	return (length);
}

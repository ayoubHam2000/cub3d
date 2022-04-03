/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_x.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:15:31 by aben-ham          #+#    #+#             */
/*   Updated: 2022/04/03 13:43:41 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static float	ray_on_x(t_player *player, int x)
{
	float	len_x;

	if (player->cos > 0)
		len_x = (player->map_x + 1 + x)	* TILE_SIZE - player->x;
	else if (player->cos < 0)
		len_x = player->x - (player->map_x - x) * TILE_SIZE;
	else
		return (INF);
	return (fabs(len_x / player->cos));
}

static int	is_hit_a_tile_x(t_player *player, float length)
{
	int	x;
	int	y;

	x = ((player->x + length * player->cos) / TILE_SIZE) + 0.000001;
	y = ((player->y + length * player->sin) / TILE_SIZE) + 0.000001;
	if (player->cos < 0)
		x--;
	return (is_tile(get_prog()->map, x, y));
}

float	ray_casting_x(t_player *player)
{
	int		x;
	float	length;

	x = 0;
	while (x < RAY_LEN)
	{
		length = ray_on_x(player, x);
		if (is_hit_a_tile_x(player, length))
			return (length);
		x++;
	}
	return (length);
}

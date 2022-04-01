/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:20:23 by aben-ham          #+#    #+#             */
/*   Updated: 2022/04/01 17:23:44 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	ray_casting(t_player *player, float angle)
{
	player->cos = cosf(angle);
	player->sin = sinf(angle);
	return (fmin(ray_casting_x(player), ray_casting_y(player)));
}

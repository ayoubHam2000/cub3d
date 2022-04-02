/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 11:35:13 by aben-ham          #+#    #+#             */
/*   Updated: 2022/04/02 14:39:34 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player_in_map()
{
	t_player	*p;
	float		angle;
	float		max_angle;
	float		length;

	p = &(get_prog()->player);
	angle = p->angle - p->view_angle / 2;
	max_angle = p->angle + p->view_angle / 2;
	while (angle < max_angle)
	{
		length = ray_casting(p, angle);
		draw_line(angle, length, p->x, p->y, 0xff00ff);
		angle += 0.01;
	}
}
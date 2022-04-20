/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prog.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 19:00:50 by aben-ham          #+#    #+#             */
/*   Updated: 2022/04/04 18:28:19 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_player(t_player *player)
{
	player->x = 0.0f;
	player->y = 0.0f;
	player->map_x = 0;
	player->map_y = 0;
	player->speed = 7;
	player->angle = 0;
	player->cos = cosf(player->angle);
	player->sin = sinf(player->angle);
	player->angle_speed = 0.05;
	player->view_angle = M_PI * 0.33;
	player->view_range = 20;
	player->mposx = 0;
}

t_prog	*get_prog(void)
{
	static t_prog	*prog;

	if (!prog)
	{
		prog = ft_malloc(sizeof(t_prog));
		prog->w_size = WIN_SIZE;
		prog->map = NULL;
		prog->img.img = NULL;
		prog->img.addr = NULL;
		prog->color = 0;
		init_player(&prog->player);
	}
	return (prog);
}

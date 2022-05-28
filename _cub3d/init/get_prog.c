/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prog.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 19:00:50 by aben-ham          #+#    #+#             */
/*   Updated: 2022/05/27 14:52:34 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_player(t_player *player)
{
	player->x = 0.0;
	player->y = 0.0;
	player->dir_x = -1.0;
	player->dir_y = 0.0;
	player->plane_x = 0.0;
	player->plane_y = 0.66;
	player->timer = 0.0;
	player->health = 200.0f;
	player->map = NULL;
}

t_prog	*get_prog(void)
{
	static t_prog	*prog;

	if (!prog)
	{
		prog = ft_malloc(sizeof(t_prog));
		prog->img.img = NULL;
		prog->img.addr = NULL;
		prog->time = 0;
		prog->old_time = 0;
		prog->pressed_key[0] = -1;
		prog->pressed_key[1] = -1;
		prog->pressed_key[2] = -1;
		prog->pressed_key[3] = -1;
		prog->m_x = WIDTH / 2;
		prog->m_y = HEIGHT / 2;
		prog->old_m_y = HEIGHT / 2;
		prog->frame = 0;
		ft_memset(prog->map_keys, 0, KEYS_MAX * sizeof(t_m_key *));
		init_player(&prog->player);
	}
	return (prog);
}

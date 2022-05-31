/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 11:52:09 by aben-ham          #+#    #+#             */
/*   Updated: 2022/05/31 20:17:42 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_sprite	*get_sprite(double x, double y, char k)
{
	t_sprite	*s;

	s = ft_malloc(sizeof(t_sprite));
	s->k = k;
	s->x = x + 0.5;
	s->y = y + 0.5;
	s->count = 100;
	s->save = 0;
	s->state = 2;
	s->is_die = 0;
	if (k == 'e')
		s->health = E_HEALTH;
	else if (k == 'm')
		s->health = M_HEALTH;
	else
		s->health = 1;
	s->hit = 0;
	return (s);
}

void	init_sprites(t_prog *prog)
{
	t_queue		*queue;
	t_sprite	**sprites;
	t_m_info	**map_info;
	int			x;
	int			y;

	map_info = prog->player.map_info;
	queue = q_init();
	y = -1;
	while (prog->player.map[++y])
	{
		x = -1;
		while(prog->player.map[y][++x])
			if (map_info[y][x].type == 'S' || map_info[y][x].type == 'Q')
				q_enqueue(queue, get_sprite(x, y, map_info[y][x].key));
	}
	sprites = ft_malloc(sizeof(t_sprite *) * (queue->len + 1));
	x = 0;
	while (queue->len)
		sprites[x++] = q_dequeue(queue);
	sprites[x] = NULL;
	prog->sprites = sprites;
}

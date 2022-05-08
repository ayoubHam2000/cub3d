/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_key_down.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 15:48:34 by aben-ham          #+#    #+#             */
/*   Updated: 2022/04/03 23:51:59 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define R_SPEED 0.08
#define M_SPEED 0.1

static void	rotate(t_player *p, int d)
{
	double	oldDirX;
	double	oldPlaneX;

	//both camera direction and camera plane must be rotated
	oldDirX = p->dir.x;
	p->dir.x = p->dir.x  * cos(R_SPEED * d) - p->dir.y * sin(R_SPEED * d);
	p->dir.y = oldDirX * sin(R_SPEED * d) + p->dir.y * cos(R_SPEED * d);
	oldPlaneX = p->plane.x;
	p->plane.x = p->plane.x * cos(R_SPEED * d) - p->plane.y * sin(R_SPEED * d);
	p->plane.y = oldPlaneX * sin(R_SPEED * d) + p->plane.y * cos(R_SPEED * d);
}

static void	move(t_player *p, char **map, int d)
{
	t_pointf	next_pos;
	int			a;

	a = 1;
	if (d == KEY_S || d == KEY_D)
		a = -1;
	if (d == KEY_W || d == KEY_S)
	{
		next_pos.x = p->pos.x + p->dir.x * M_SPEED * a;
		next_pos.y = p->pos.y + p->dir.y * M_SPEED * a;
	}
	else if(d == KEY_A || d == KEY_D)
	{
		next_pos.x = p->pos.x - p->dir.y * M_SPEED * a;
		next_pos.y = p->pos.y + p->dir.x * M_SPEED * a;
	}
    if(map[(int)p->pos.y][(int)next_pos.x] != '1')
		p->pos.x = next_pos.x;
	if(map[(int)next_pos.y][(int)p->pos.x] != '1')
		p->pos.y = next_pos.y;
}

int	on_key_down(int keycode, t_prog *prog)
{
	t_player	*p;

	p = &prog->player;
	if (keycode == KEY_L)
		rotate(p, -1);
	else if (keycode == KEY_R)
		rotate(p, 1);
	else if (keycode == KEY_W || keycode == KEY_S || keycode == KEY_A || keycode == KEY_D)
		move(p, prog->map->map, keycode);
	//printf("%d %0.2f %0.2f|%0.2f %0.2f|%.2f %.2f\n",keycode, p->pos.x, p->pos.y, p->dir.x, p->dir.y, p->plane.x, p->plane.y);
	game_frame(prog);
	return (1);
}

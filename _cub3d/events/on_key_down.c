/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_key_down.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 15:48:34 by aben-ham          #+#    #+#             */
/*   Updated: 2022/05/21 20:26:39 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define R_SPEED 0.06
#define M_SPEED 0.11

static void	rotate(int keycode, t_player *p)
{
	double	d;
	double	oldDirX;
	double	oldPlaneX;

	d = 1;
	if (keycode == KEY_L)
		d = -1;
	if (get_prog()->pressed_key[1] != -1)
		d *= 0.75;
	oldDirX = p->dir_x;
	p->dir_x = p->dir_x  * cos(R_SPEED * d) - p->dir_y * sin(R_SPEED * d);
	p->dir_y = oldDirX * sin(R_SPEED * d) + p->dir_y * cos(R_SPEED * d);
	oldPlaneX = p->plane_x;
	p->plane_x = p->plane_x * cos(R_SPEED * d) - p->plane_y * sin(R_SPEED * d);
	p->plane_y = oldPlaneX * sin(R_SPEED * d) + p->plane_y * cos(R_SPEED * d);
}

static void	rotate_mouse(t_prog *prog)
{
	double		oldDirX;
	double		oldPlaneX;
	t_player	*p;
	double		d;
	static int huh;

	if (huh == prog->m_x)
		return ;
	p = &prog->player;
	oldDirX = p->dir_x;
	d = (prog->old_m_x - prog->m_x) * 0.17;
	p->dir_x = p->dir_x  * cos(R_SPEED * d) - p->dir_y * sin(R_SPEED * d);
	p->dir_y = oldDirX * sin(R_SPEED * d) + p->dir_y * cos(R_SPEED * d);
	oldPlaneX = p->plane_x;
	p->plane_x = p->plane_x * cos(R_SPEED * d) - p->plane_y * sin(R_SPEED * d);
	p->plane_y = oldPlaneX * sin(R_SPEED * d) + p->plane_y * cos(R_SPEED * d);
	huh = prog->m_x;
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
		next_pos.x = p->x + p->dir_x * M_SPEED * a;
		next_pos.y = p->y + p->dir_y * M_SPEED * a;
	}
	else if(d == KEY_A || d == KEY_D)
	{
		next_pos.x = p->x - p->dir_y * M_SPEED * a;
		next_pos.y = p->y + p->dir_x * M_SPEED * a;
	}
	if (p->map[(int)p->y][(int)next_pos.x] != '1')
		p->x = next_pos.x;
	if (p->map[(int)next_pos.y][(int)p->x] != '1')
		p->y = next_pos.y;
}

void	perform_events(t_prog *prog)
{
	t_player	*p;

	p = &prog->player;
	if (prog->pressed_key[0] != -1)
		rotate(prog->pressed_key[0], p);
	if (prog->pressed_key[1] != -1)
		move(p, prog->player.map, prog->pressed_key[1]);
	if (prog->pressed_key[2] != -1)
		move(p, prog->player.map, prog->pressed_key[2]);
	//rotate_mouse(prog);
	prog->m_y = prog->old_m_y;
}

int	on_key_down(int keycode, t_prog *prog)
{
	if (keycode == KEY_L || keycode == KEY_R)
		prog->pressed_key[0] = keycode;
	else if (keycode == KEY_S || keycode == KEY_W)
		prog->pressed_key[1] = keycode;
	else if (keycode == KEY_A || keycode == KEY_D)
		prog->pressed_key[2] = keycode;
	return (0);
}

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

#define KEY_SP 16
#define KEY_AR 32
#define KEY_AS 34
#define KEY_PR 31
#define KEY_dx 38
#define KEY_dy 40
#define KEY_REVERSE 44

#define HIT_LEN 2

t_point	is_can_move(t_player *player, float angle)
{
	float	ray;
	t_point	res;

	ray = ray_casting(player, M_PI * angle);
	res.x = fabs(cosf(M_PI * angle) * ray);
	res.y = fabs(sinf(M_PI * angle) * ray);
	return (res);
}

int	on_key_down(int keycode, t_prog *prog)
{
	static int	reverse = 1;
	int			move;
	t_player	*player;
	t_pointf	p;

	player = &(prog->player);
	
	p.x = 0;
	p.y = 0;
	if (keycode == KEY_W || keycode == KEY_S)
	{
		move = 1;
		if (keycode == KEY_S)
			move = -1;
		p.x = cosf(player->angle) * move;
		p.y = sinf(player->angle) * move;
	}
	else if (keycode == KEY_A || keycode == KEY_D)
	{
		move = 1;
		if (keycode == KEY_A)
			move = -1;
		p.x = cosf(M_PI * 0.5 + player->angle) * move;
		p.y = sinf(M_PI * 0.5 + player->angle) * move;
	}
	//p.x *= 5;
	//p.y *= 5;
	move = 0;
	while (move < player->speed)
	{
		if (p.x < 0 && is_can_move(player, 0.75f).y > HIT_LEN && is_can_move(player, 1.25f).y > HIT_LEN && ray_casting(player, M_PI) > HIT_LEN + 1)
			player->x += p.x;
		if (p.x > 0 && is_can_move(player, 0.25f).y > HIT_LEN && is_can_move(player, 1.75f).y > HIT_LEN && ray_casting(player, 0) > HIT_LEN + 1)
			player->x += p.x;
		if (p.y < 0 && is_can_move(player, 1.25f).x > HIT_LEN && is_can_move(player, 1.75f).x > HIT_LEN && ray_casting(player, M_PI * 1.5f) > HIT_LEN + 1)
			player->y += p.y;
		if (p.y > 0 && is_can_move(player, 0.25f).x > HIT_LEN && is_can_move(player, 0.75f).x > HIT_LEN && ray_casting(player, M_PI * 0.5f) > HIT_LEN + 1)
			player->y += p.y;
		move++;
	}
	/*while (move < player->speed)
	{
		if (keycode == KEY_A && is_can_move(player, 0.75f).y > HIT_LEN && is_can_move(player, 1.25f).y > HIT_LEN && ray_casting(player, M_PI) > HIT_LEN + 1)
			player->x--;
		if (keycode == KEY_D && is_can_move(player, 0.25f).y > HIT_LEN && is_can_move(player, 1.75f).y > HIT_LEN && ray_casting(player, 0) > HIT_LEN + 1)
			player->x++;
		if (keycode == KEY_W && is_can_move(player, 1.25f).x > HIT_LEN && is_can_move(player, 1.75f).x > HIT_LEN && ray_casting(player, M_PI * 1.5f) > HIT_LEN + 1)
			player->y--;
		if (keycode == KEY_S && is_can_move(player, 0.25f).x > HIT_LEN && is_can_move(player, 0.75f).x > HIT_LEN && ray_casting(player, M_PI * 0.5f) > HIT_LEN + 1)
			player->y++;
		move++;
	}*/
	
	if (keycode == KEY_L)
		player->angle -= player->angle_speed;
	else if (keycode == KEY_R)
		player->angle += player->angle_speed;
	else if (keycode == KEY_SP)
		player->speed += 1 * reverse;
	else if (keycode == KEY_AR)
		player->view_angle += 0.01 * reverse;
	else if (keycode == KEY_AS)
		player->angle_speed += 0.01 * reverse;
	else if (keycode == KEY_PR)
		player->view_range += 1 * reverse;
	else if (keycode == KEY_REVERSE)
		reverse *= -1;
	
	if (player->angle < 0)
		player->angle += 2 * M_PI;
	else if (player->angle > 2 * M_PI)
		player->angle = 0.0f;
	player->cos = cosf(player->angle);
	player->sin = sinf(player->angle);
	player->map_x = player->x / TILE_SIZE;
	player->map_y = player->y / TILE_SIZE;
	
	printf("key:%d => p(%f, %f, %f) - (%d, %d) info(%d)(sp:%f, ar:%f, as:%f, pr:%f) (cos:%f, sin:%f)\n", keycode,
		player->x, player->y, player->angle, player->map_x, player->map_y, reverse,
		player->speed, player->view_angle, player->angle_speed, player->view_range,
		player->cos, player->sin
		);

	game_frame(prog);
	return (0);
}

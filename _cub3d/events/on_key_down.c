/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_key_down.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 15:48:34 by aben-ham          #+#    #+#             */
/*   Updated: 2022/04/01 17:59:55 by aben-ham         ###   ########.fr       */
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

int	on_key_down(int keycode, t_prog *prog)
{
	static int	reverse = 1;
	int			move;
	t_point		limitx;
	t_point		limity;
	t_player	*player;

	player = &(prog->player);
	
	limitx.x = ray_casting(player, 0);
	limitx.y = ray_casting(player, M_PI);
	limity.x = ray_casting(player, M_PI * 0.5f);
	limity.y = ray_casting(player, M_PI * 1.5f);
	
	move = player->speed;
	while (move)
	{
		if (keycode == KEY_A && limitx.y > HIT_LEN)
			player->x--;
		else if (keycode == KEY_D && limitx.x > 2 * HIT_LEN)
			player->x++;
		else if (keycode == KEY_W && limity.y > HIT_LEN)
			player->y--;
		else if (keycode == KEY_S && limity.x > 2 * HIT_LEN)
			player->y++;
		move--;
	}
	
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_mouse_down.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 15:48:34 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/30 14:55:18 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray_casting(t_prog *prog)
{
	int	x;
	int	y;

	x = prog->player.x;
	y = prog->player.y;
	
}

int	on_key_down(int keycode, t_prog *prog)
{
	const int	i = 20;

	if (keycode == KEY_A)
		prog->player.x += i;
	else if (keycode == KEY_D)
		prog->player.x -= i;
	else if (keycode == KEY_W)
		prog->player.y += i;
	else if (keycode == KEY_S)
		prog->player.y -= i;
	else if (keycode == 3)
		prog->player.dx += 10;
	else if (keycode == 5)
		prog->player.dx -= 10;
	else if (keycode == 4)
		prog->player.angle = (int)(prog->player.angle + 4);
	else if (keycode == 38)
		prog->player.angle = (int)(prog->player.angle - 4);
	//printf("%d, (%f, %f)\n",keycode, prog->player.x, prog->player.y);
	game_frame(prog);
	return (0);
}

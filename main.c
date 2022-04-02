/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 13:38:46 by aben-ham          #+#    #+#             */
/*   Updated: 2022/04/02 12:49:19 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	change_angle(t_player *player, char c)
{
	if (c == 'N')
		player->angle = M_PI * 1.5;
	else if (c == 'S')
		player->angle = M_PI * 0.5;
	else if (c == 'E')
		player->angle = 0.0f;
	else if (c == 'W')
		player->angle = M_PI;
}

void	init_player_pos(void)
{
	int		x;
	int		y;
	t_prog	*prog;
	char	**map;

	prog = get_prog();
	map = prog->map->map;
	x = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (ft_in(map[x][y], "NSEW"))
			{
				prog->player.x = y * TILE_SIZE + TILE_SIZE * 0.5;
				prog->player.y = x * TILE_SIZE + TILE_SIZE * 0.5;
				prog->player.map_x = y;
				prog->player.map_y = x;
				change_angle(&prog->player, map[x][y]);
				return ;
			}
			y++;
		}
		x++;
	}
}

int	start_cub3d(char *file)
{
	t_prog	*prog;

	prog = get_prog();
	if (!init_mlx(prog))
		return (0);
	prog->map = get_map(file);	
	if (!prog || !prog->map)
	{
		printf("Error\n");
		return (0);
	}
	init_player_pos();
	game_frame(prog);
	mlx_hook(prog->win, ON_KEYDOWN, 0, on_key_down, prog);
	mlx_hook(prog->win, ON_KEYUP, 0, on_key_up, prog);
	mlx_hook(prog->win, ON_DESTROY, 0, exit_cube3d, prog);
	mlx_loop(prog->mlx);
	return (1);
}

int	main(int ac, char **av)
{
	if (check_arg(ac, av))
	{
		if (start_cub3d(av[1]))
			return (0);
		return (1);
	}
	return (1);
}

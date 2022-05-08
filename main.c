/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 13:38:46 by aben-ham          #+#    #+#             */
/*   Updated: 2022/04/03 23:52:47 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player_pos(void)
{
	int		x;
	int		y;
	t_prog	*prog;
	char	**map;

	prog = get_prog();
	map = prog->map->map;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (ft_in(map[y][x], "NSEW"))
			{
				prog->player.pos.x = (double)x;
				prog->player.pos.y = (double)y;
				prog->player.dir.x = -1.0;
				prog->player.dir.y = 0.0;
				prog->player.plane.x = 0.0;
				prog->player.plane.y = 0.66;
				return ;
			}
			x++;
		}
		y++;
	}
}

int	start_cub3d(char *file)
{
	t_prog	*prog;

	prog = get_prog();
	if (!init_mlx(prog))
		return (0);
	prog->map = get_map(file);
	if (!prog || !prog->map || !load_textures(prog))
	{
		write(2, "Error\n", 6);
		return (0);
	}
	init_player_pos();
	game_frame(prog);
	mlx_hook(prog->win, ON_KEYDOWN, 1, on_key_down, prog);
	mlx_hook(prog->win, ON_KEYUP, 1L<<1, on_key_up, prog);
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

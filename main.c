/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 13:38:46 by aben-ham          #+#    #+#             */
/*   Updated: 2022/05/14 14:44:36 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player_direction(char direction, t_player *p)
{
	double	angle;
	double	old_dir_x;
	double	old_plane_x;

	p->dir_x = -1.0;
	p->dir_y = 0.0;
	p->plane_x = 0.0;
	p->plane_y = 0.66;
	if (direction == 'E')
		angle = M_PI;
	else if (direction == 'N')
		angle = M_PI_2;
	else if (direction == 'S')
		angle = M_PI * 1.5;
	else
		return ;
	old_dir_x = p->dir_x;
	p->dir_x = p->dir_x  * cos(angle) - p->dir_y * sin(angle);
	p->dir_y = old_dir_x * sin(angle) + p->dir_y * cos(angle);
	old_plane_x = p->plane_x;
	p->plane_x = p->plane_x * cos(angle) - p->plane_y * sin(angle);
	p->plane_y = old_plane_x * sin(angle) + p->plane_y * cos(angle);
}

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
				prog->player.x = (double)x + 0.1;
				prog->player.y = (double)y + 0.1;
				init_player_direction(map[y][x], &prog->player);
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
	mlx_hook(prog->win, ON_MOUSEMOVE, 0, on_mouse_move, prog);
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
